pub struct TreeDecomposition {
    root: usize,
    parent: Vec<usize>,
    size: Vec<usize>,
    // invariant: chain[start[i]][index[i]] == i
    start: Vec<usize>,
    index: Vec<usize>,
    chain: Vec<Vec<usize>>,
    // invariant: id[ts[i]] == i
    id: Vec<usize>,
    ts: Vec<usize>, // timestamp, index used in SegTree
}

pub struct TreeDecompositionIter<'a> {
    td: &'a TreeDecomposition,
    current: usize,
    ancestor: usize,
}

impl<'a> Iterator for TreeDecompositionIter<'a> {
    type Item = (usize, usize); // [a, b)

    fn next(&mut self) -> Option<Self::Item> {
        if self.current == usize::MAX {
            return None;
        }
        let start = self.td.start[self.current];
        if start == self.td.start[self.ancestor] {
            let item = (self.td.ts[self.ancestor], self.td.ts[self.current] + 1);
            self.current = usize::MAX;
            Some(item)
        } else {
            let item = (self.td.ts[start], self.td.ts[self.current] + 1);
            self.current = self.td.parent[start];
            Some(item)
        }
    }
}

// Heavy-Light Decomposition
impl TreeDecomposition {
    fn dfs(&mut self, e: &Vec<Vec<usize>>, v: usize, p: usize) -> usize {
        let mut size = 1;
        for &w in &e[v] {
            if w != p {
                size += self.dfs(e, w, v);
            }
        }
        self.parent[v] = p;
        self.size[v] = size;
        size
    }

    fn decomp(
        &mut self,
        e: &Vec<Vec<usize>>,
        v: usize,
        p: usize,
        k: usize,
        mut ts: usize,
    ) -> usize {
        self.start[v] = k;
        self.index[v] = self.chain[k].len();
        self.chain[k].push(v);
        self.ts[v] = ts;
        self.id[ts] = v;
        ts += 1;

        let mut maxw = v;
        for &w in &e[v] {
            if w != p && (maxw == v || self.size[w] > self.size[maxw]) {
                maxw = w;
            }
        }
        if maxw != v {
            ts = self.decomp(e, maxw, v, k, ts);
        }

        for &w in &e[v] {
            if w != p && w != maxw {
                ts = self.decomp(e, w, v, w, ts);
            }
        }
        ts
    }

    pub fn new(tree: &Vec<Vec<usize>>, root: usize) -> Self {
        let n = tree.len();
        let mut t = Self {
            root: root,
            parent: vec![0; n],
            size: vec![0; n],
            start: vec![0; n],
            index: vec![0; n],
            chain: vec![vec![]; n],
            id: vec![0; n],
            ts: vec![0; n],
        };
        t.dfs(tree, root, root);
        t.decomp(tree, root, root, root, 0);
        t
    }

    pub fn path_to_root(&self, v: usize) -> TreeDecompositionIter {
        TreeDecompositionIter {
            td: &self,
            current: v,
            ancestor: self.root,
        }
    }

    pub fn path_to_ancestor(&self, v: usize, ancestor: usize) -> TreeDecompositionIter {
        debug_assert!(self.lca(v, ancestor) == ancestor);
        TreeDecompositionIter {
            td: &self,
            current: v,
            ancestor: ancestor,
        }
    }

    pub fn lca(&self, a: usize, b: usize) -> usize {
        let mut pa = self.path_to_root(a).collect::<Vec<_>>();
        let mut pb = self.path_to_root(b).collect::<Vec<_>>();
        pa.reverse();
        pb.reverse();
        debug_assert!(pa[0].0 == 0 && pb[0].0 == 0);
        let mut i = 1;
        while i < pa.len() && i < pb.len() && pa[i].0 == pb[i].0 {
            i += 1;
        }
        i -= 1;
        self.id[pa[i].1.min(pb[i].1) - 1]
    }
}

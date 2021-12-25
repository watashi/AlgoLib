struct DisjointSet {
    p: Vec<usize>,
}

impl DisjointSet {
    fn new(n: usize) -> DisjointSet {
        DisjointSet {
            p: (0..n).collect(),
        }
    }

    fn getp(&mut self, x: usize) -> usize {
        if self.p[x] != x {
            self.p[x] = self.getp(self.p[x]);
        }
        self.p[x]
    }

    fn setp(&mut self, x: usize, y: usize) -> Option<(usize, usize)> {
        let x = self.getp(x);
        let y = self.getp(y);
        self.p[x] = y;
        if x != y {
            Some((x, y))
        } else {
            None
        }
    }
}

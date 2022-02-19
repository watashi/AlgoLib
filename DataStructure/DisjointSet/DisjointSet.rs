pub struct DisjointSet(Vec<usize>);

impl DisjointSet {
    pub fn new(n: usize) -> Self {
        DisjointSet((0..n).collect())
    }

    pub fn clear(&mut self) {
        self.0.iter_mut().enumerate().for_each(|(i, j)| *j = i);
    }

    pub fn getp(&mut self, x: usize) -> usize {
        if self.0[x] != x {
            self.0[x] = self.getp(self.0[x]);
        }
        self.0[x]
    }

    pub fn setp(&mut self, x: usize, y: usize) -> Option<(usize, usize)> {
        let x = self.getp(x);
        let y = self.getp(y);
        self.0[x] = y;
        if x != y {
            Some((x, y))
        } else {
            None
        }
    }
}

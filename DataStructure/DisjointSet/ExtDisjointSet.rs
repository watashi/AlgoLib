
pub struct ExtDisjointSet(Vec<i32>);

impl ExtDisjointSet {
    pub fn new(n: i32) -> Self {
        Self((0..n).collect())
    }

    pub fn getp(&mut self, x: i32) -> i32 {
        if x < 0 {
            !self.getp(!x)
        } else {
            let i = x as usize;
            if self.0[i] == x {
                x
            } else {
                self.0[i] = self.getp(self.0[i]);
                self.0[i]
            }
        }
    }

    pub fn setp(&mut self, x: i32, y: i32) -> Result<(i32, i32), bool> {
        let x = self.getp(x);
        let y = self.getp(y);
        if x == y {
            Err(true)
        } else if x == !y {
            Err(false)
        } else {
            let (x, y) = if x >= 0 { (x, y) } else { (!x, !y) };
            self.0[x as usize] = y;
            Ok((x, y))
        }
    }
}

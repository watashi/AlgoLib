pub struct BIT<T>(Vec<T>);

impl<T: Clone + Copy + Default + ops::AddAssign + ops::Sub<Output = T>> BIT<T> {
    pub fn new(n: usize) -> Self {
        Self(vec![Default::default(); n + 1])
    }

    pub fn add(&mut self, mut i: usize, v: T) {
        i += 1;
        while i < self.0.len() {
            self.0[i] += v;
            i = (i | (i - 1)) + 1;
        }
    }

    pub fn partial_sum(&self, mut i: usize) -> T {
        let mut s = Default::default();
        while i > 0 {
            s += self.0[i];
            i = i & (i - 1);
        }
        s
    }

    pub fn sum(&self, range: impl ops::RangeBounds<usize>) -> T {
        use ops::Bound::*;
        let start = match range.start_bound() {
            Included(&i) => i,
            Excluded(&i) => i + 1,
            Unbounded => 0,
        };
        let end = match range.end_bound() {
            Included(&i) => i + 1,
            Excluded(&i) => i,
            Unbounded => self.0.len() - 1,
        };
        if start < end {
            self.partial_sum(end) - self.partial_sum(start)
        } else {
            Default::default()
        }
    }

    pub fn get(&self, i: usize) -> T {
        self.sum(i..=i)
    }

    pub fn set(&mut self, i: usize, v: T) {
        self.add(i, v - self.get(i))
    }
}

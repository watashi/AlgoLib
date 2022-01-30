pub struct RMQ<T> {
    index: Vec<Vec<usize>>,
    value: Vec<T>,
}

impl<T: Ord> RMQ<T> {
    fn min(v: &Vec<T>, i: usize, j: usize) -> usize {
        if v[i].cmp(&v[j]).is_le() {
            i
        } else {
            j
        }
    }

    pub fn new(value: Vec<T>) -> Self {
        let mut index = vec![];
        let mut prev = (0..value.len()).collect::<Vec<_>>();
        let mut step = 1;
        while !prev.is_empty() {
            let next = prev
                .iter()
                .zip(prev.iter().skip(step))
                .map(|(&i, &j)| Self::min(&value, i, j))
                .collect();
            index.push(prev);
            prev = next;
            step *= 2;
        }
        RMQ {
            index: index,
            value: value,
        }
    }

    pub fn index(&self, start: usize, end: usize) -> usize {
        let n = (usize::BITS - (end - start).leading_zeros() - 1) as usize;
        Self::min(
            &self.value,
            self.index[n][start],
            self.index[n][end - (1 << n)],
        )
    }

    pub fn value(&self, start: usize, end: usize) -> &T {
        &self.value[self.index(start, end)]
    }
}

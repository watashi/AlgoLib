type SegTreeIndex = i32;

pub trait SegTreeMonoid: Copy {
    fn empty(start: SegTreeIndex, end: SegTreeIndex) -> Self;
    fn append(&self, other: &Self) -> Self;
}

pub trait SegTreeOp<T>: Copy {
    fn apply(&self, start: SegTreeIndex, end: SegTreeIndex, value: &mut T);
    fn combine(&mut self, other: &Self);
}

impl<T: SegTreeMonoid> SegTreeOp<T> for T {
    fn apply(&self, _: SegTreeIndex, _: SegTreeIndex, value: &mut T) {
        *value = value.append(self);
    }

    fn combine(&mut self, other: &Self) {
        *self = self.append(other);
    }
}

pub struct SegTree<T, Op> {
    start: SegTreeIndex,
    end: SegTreeIndex,
    value: T,
    op: Option<Op>,
    left: Option<Box<Self>>,
    right: Option<Box<Self>>,
}

impl<T: SegTreeMonoid, Op: SegTreeOp<T>> SegTree<T, Op> {
    pub fn new(start: SegTreeIndex, end: SegTreeIndex) -> Self {
        SegTree {
            start: start,
            end: end,
            value: T::empty(start, end),
            op: None,
            left: None,
            right: None,
        }
    }

    pub fn is_leaf(&self) -> bool {
        self.end - self.start == 1
    }

    fn lazy_apply(&mut self, op: Op) {
        op.apply(self.start, self.end, &mut self.value);
        if !self.is_leaf() {
            match self.op.as_mut() {
                Some(x) => {
                    x.combine(&op);
                }
                None => self.op = Some(op),
            }
        }
    }

    fn force(&mut self) -> (&mut Self, &mut Self) {
        debug_assert!(!self.is_leaf());
        if self.left.is_none()
        /* && self.right.is_none() */
        {
            let mid = (self.start + self.end) / 2;
            self.left = Some(Box::new(Self::new(self.start, mid)));
            self.right = Some(Box::new(Self::new(mid, self.end)));
        }
        let left = self.left.as_deref_mut().unwrap();
        let right = self.right.as_deref_mut().unwrap();
        if let Some(op) = self.op {
            left.lazy_apply(op);
            right.lazy_apply(op);
            self.op = None;
        }
        (left, right)
    }

    pub fn apply(&mut self, start: SegTreeIndex, end: SegTreeIndex, op: Op) {
        debug_assert!(start < self.end && self.start < end && start < end);
        if start <= self.start && self.end <= end {
            self.lazy_apply(op);
        } else {
            let (left, right) = self.force();
            if start < left.end {
                left.apply(start, end, op);
            }
            if right.start < end {
                right.apply(start, end, op);
            }
            self.value = left.value.append(&right.value);
        }
    }

    pub fn query(&mut self, start: SegTreeIndex, end: SegTreeIndex) -> T {
        debug_assert!(start < self.end && self.start < end && start < end);
        if start <= self.start && self.end <= end {
            self.value
        } else {
            let (left, right) = self.force();
            if end <= left.end {
                left.query(start, end)
            } else if right.start <= start {
                right.query(start, end)
            } else {
                left.query(start, end).append(&right.query(start, end))
            }
        }
    }

    pub fn bsearch<F>(&mut self, start: SegTreeIndex, end: SegTreeIndex, f: &F) -> SegTreeIndex
    where
        F: Fn(&T) -> bool,
    {
        debug_assert!(start < self.end && self.start < end && start < end);
        if !f(&self.value) {
            end
        } else if self.is_leaf() {
            self.start
        } else {
            let (left, right) = self.force();
            if end <= left.end {
                left.bsearch(start, end, f)
            } else if right.start <= start {
                right.bsearch(start, end, f)
            } else {
                let ret = left.bsearch(start, end, f);
                if ret != end {
                    ret
                } else {
                    right.bsearch(start, end, f)
                }
            }
        }
    }
}

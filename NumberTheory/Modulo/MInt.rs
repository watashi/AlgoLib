type MIntImpl = u64;

#[derive(Clone, Copy, Debug, Default)]
pub struct MIntT<const M: MIntImpl>(MIntImpl);

impl<const M: MIntImpl> From<MIntImpl> for MIntT<M> {
    fn from(x: MIntImpl) -> Self {
        Self(x % M)
    }
}

impl<const M: MIntImpl> ops::Add for MIntT<M> {
    type Output = Self;
    fn add(mut self, rhs: Self) -> Self::Output {
        self += rhs;
        self
    }
}

impl<const M: MIntImpl> ops::AddAssign for MIntT<M> {
    fn add_assign(&mut self, rhs: Self) {
        self.0 += rhs.0;
        if self.0 >= M {
            self.0 -= M;
        }
    }
}

impl<const M: MIntImpl> ops::Sub for MIntT<M> {
    type Output = Self;
    fn sub(mut self, rhs: Self) -> Self::Output {
        self -= rhs;
        self
    }
}

impl<const M: MIntImpl> ops::SubAssign for MIntT<M> {
    fn sub_assign(&mut self, rhs: Self) {
        if self.0 < rhs.0 {
            self.0 += M;
        }
        self.0 -= rhs.0;
    }
}

impl<const M: MIntImpl> ops::Mul for MIntT<M> {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self(self.0 * rhs.0 % M)
    }
}

impl<const M: MIntImpl> ops::MulAssign for MIntT<M> {
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}

impl<const M: MIntImpl> ops::Div for MIntT<M> {
    type Output = Self;
    fn div(self, rhs: Self) -> Self::Output {
        self * rhs.inv()
    }
}

impl<const M: MIntImpl> ops::DivAssign for MIntT<M> {
    fn div_assign(&mut self, rhs: Self) {
        *self *= rhs.inv();
    }
}

impl<const M: MIntImpl> MIntT<M> {
    fn pow(&self, mut b: u64) -> Self {
        let mut a = *self;
        let mut c = 1.into();
        loop {
            if (b & 1) != 0 {
                c *= a;
            }
            b >>= 1;
            if b == 0 {
                break;
            }
            a *= a;
        }
        c
    }

    fn inv(&self) -> Self {
        self.pow((M - 2) as u64)
    }
}

type MInt = MIntT<1_000_000_007>;

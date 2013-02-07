template<typename Base, typename I>
struct Ring: public Base {
  typedef typename Base::T T;

  Ring(const Base& base): Base(base) { }

  T pow(T a, I b) const {
    T c = this->unit();
    while (b > 0) {
      if ((b & 1) != 0) {
        c = this->mul(c, a);
      }
      b >>= 1;
      if (b != 0) {
        a = this->mul(a, a);
      }
    }
    return c;
  }

  T sum(const T& a, I b) const {
    if (b == 0) {
      return this->zero();
    } else if ((b & 1) != 0) {
      --b;
      return this->add(sum(a, b), pow(a, b));
    } else {
      b >>= 1;
      return this->mul(sum(a, b), this->add(this->unit(), pow(a, b)));
    }
  }
};


/**
 * test program
 */
#include <iostream>
#include "../Matrix/Matrix.cpp"

using namespace std;

template<typename I>
struct ModOp {
  typedef I T;

  const T MOD;

  ModOp(const T& mod): MOD(mod) { }
  T zero() const { return 0; }
  T unit() const { return 1 % MOD; }
  T add(const T& lhs, const T& rhs) const { return (lhs + rhs) % MOD; }
  T mul(const T& lhs, const T& rhs) const { return (lhs * rhs) % MOD; }
};

struct MatrixOp {
  typedef Matrix T;

  const int SIZE;
  const long long MOD;

  MatrixOp(int size, long long mod): SIZE(size), MOD(mod) {
  }

  T zero() const {
    T ret;
    ret.fill(SIZE, SIZE);
    return ret;
  }

  T unit() const {
    T ret;
    ret.eye(SIZE);
    return ret;
  }

  T add(const T& lhs, const T& rhs) const {
    T ret;
    ::add(lhs, rhs, MOD, ret);
    return ret;
  }

  T mul(const T& lhs, const T& rhs) const {
    T ret;
    ::mul(lhs, rhs, MOD, ret);
    return ret;
  }
};

using namespace std;

typedef Ring<ModOp<long long>, long long> ModRing;
typedef Ring<MatrixOp, long long> MatrixRing;

const int MOD = 1000000007LL;

int main() {
  long long a, b;
  ModRing mr = ModRing(ModOp<long long>(MOD));

  cin >> a >> b;
  cout << mr.pow(a, b) << endl;
  cout << mr.sum(a, b) << endl;

  return 0;
}

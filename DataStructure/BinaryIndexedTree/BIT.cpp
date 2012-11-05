template<int MAXN, typename T = int>
struct BIT {
  int n;
  T a[MAXN];

  void init(int n) {
    this->n = n;
    fill(a, a + n + 1, T());
  }

  void add(int i, T v) {
    for (int j = i + 1; j <= n; j = (j | (j - 1)) + 1) {
      a[j] += v;
    }
  }

  // [0, i)
  T sum(int i) const {
    T ret = T();
    for (int j = i; j > 0; j = j & (j - 1)) {
      ret += a[j];
    }
    return ret;
  }

  T get(int i) const {
    return sum(i + 1) - sum(i);
  }

  void set(int i, T v) {
    add(i, v - get(i));
  }
};


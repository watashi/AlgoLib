
template<int N> struct LG2 { static const int VAL = LG2<N / 2>::VAL + 1; };
template<> struct LG2<0> { static const int VAL = -1; };

template<int MAXN, typename T = int>
struct RMQ {
  // static const int MAXL = 32 - __builtin_clz(MAXN - 1);
  static const int MAXL = ::LG2<MAXN - 1>::VAL + 1;

  int n;
  T e[MAXN];
  int rmq[MAXL][MAXN];

  static inline int LG2(int i) { return 31 - __builtin_clz(i); }
  static inline int BIN(int i) { return 1 << i; }

  int cmp(int l, int r) {
    return e[l] <= e[r] ? l : r;
  }

  void init(int n, int e[MAXN]) {
    this->n = n;
    copy(e, e + n, this->e);
    for (int i = 0; i < n; ++i) {
      rmq[0][i] = i;
    }
    for (int i = 0; BIN(i + 1) <= n; ++i) {
      for (int j = 0; j + BIN(i + 1) <= n; ++j) {
        rmq[i + 1][j] = cmp(rmq[i][j], rmq[i][j + BIN(i)]);
      }
    }
  }

  int index(int l, int r) {
    int b = LG2(r - l);
    return cmp(rmq[b][l], rmq[b][r - (1 << b)]);
  }

  T value(int l, int r) {
    return e[index(l, r)];
  }
};

RMQ<MAXN> rmq;


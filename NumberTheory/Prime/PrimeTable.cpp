struct PrimeTable {
  vector<int> p;

  PrimeTable(int n) {
    init(n);
  }

  void init(int n) {
    p = vector<int>(n, 0);
    iota(p.begin(), p.end(), 0);
    for (int i = 2; i * i < n; ++i) {
      if (p[i] == i) {
        for (int j = i * i; j < n; j += i) {
          if (p[j] == j) {
            p[j] = i;
          }
        }
      }
    }
  }

  vector<pair<int, int>> pfactors(int n) const {
    vector<pair<int, int>> d;
    while (n > 1) {
      int q = p[n], r = 0;
      do {
        n /= q;
        ++r;
      } while (n % q == 0);
      d.emplace_back(q, r);
    }
    return d;
  }
};

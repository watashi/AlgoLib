#include <vector>

using namespace std;

struct ExtDisjointSet {
  vector<int> p, s, t;

  static inline int RE(int i) { return ~i; }  // !!

  void init(int n) {
    p.resize(n);
    s.resize(n);
    t.resize(n);
    for (int i = 0; i < n; ++i) {
      p[i] = i;
      s[i] = 1;
      t[i] = 0;
    }
  }

  int getp(int i) {
    if (i < 0) {
      return RE(getp(RE(i)));
    } else if (i == p[i]) {
      return i;
    } else {
      return p[i] = getp(p[i]);
    }
  }

  int setp(int i, int j) {
    i = getp(i);
    j = getp(j);
    if (i == j) {
      return 0;
    } else if (i == RE(j)) {
      return -1;
    } else {
      if (i < 0) {
        i = RE(i);
        j = RE(j);
      }
      p[i] = j;
      if (j >= 0) {
        s[j] += s[i];
        t[j] += t[i];
      } else {
        s[RE(j)] += t[i];
        t[RE(j)] += s[i];
      }
      return 1;
    }
  }
} eds;


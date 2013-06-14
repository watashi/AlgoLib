#include <utility>

using namespace std;

template<typename T>
struct Indexer {
  const T* a;

  Indexer(const T* a): a(a) {
  }

  bool operator()(int lhs, int rhs) const {
    return a[lhs] < a[rhs];
  }
};

template<int MAXN>
struct SuffixArray {
  int sa[MAXN], rank[MAXN], height[MAXN];

  void init(int n, const char a[MAXN]) {
    if (n == 1) {
      sa[0] = rank[0] = 0;
      return;
    }

    for (int i = 0; i < n; ++i) {
      rank[i] = a[i];
    }
    for (int m = 1; m < n; m <<= 1) {
      static pair<int, int> suffix[MAXN];
      for (int i = 0; i < n; ++i) {
        sa[i] = i;
        suffix[i] = make_pair(rank[i], i + m < n ? rank[i + m] : -1);
      }
      sort(sa, sa + n, Indexer<pair<int, int> >(suffix));
      for (int i = 0; i < n; ++i) {
        if (i == 0 || (suffix[sa[i]] != suffix[sa[i - 1]])) {
          rank[sa[i]] = i;
        } else {
          rank[sa[i]] = rank[sa[i - 1]];
        }
      }
    }

    static int h[MAXN];
    for (int i = 0; i < n; ++i) {
      if (rank[i] == 0) {
        h[i] = 0;
      } else {
        int x = i, y = sa[rank[i] - 1], z = max(0, h[i - 1] - 1);
        while (x + z < n && y + z < n && a[x + z] == a[y + z]) {
          ++z;
        }
        h[i] = z;
      }
    }
    for (int i = 0; i < n; ++i) {
      height[i] = h[sa[i]];
    }
  }
};

SuffixArray<1 << 17> sa;


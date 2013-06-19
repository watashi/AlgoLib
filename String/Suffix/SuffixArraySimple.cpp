#include "SuffixArrayBase.cpp"
#include <utility>
#include <algorithm>

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

struct SuffixArraySimple: SuffixArrayBase {
  template<typename T>
  void init(int n, const T a[]) {
    sa.resize(n);
    rank.resize(n);

    for (int i = 0; i < n; ++i) {
      rank[i] = a[i];
    }
    for (int m = 1; (m == 1 && n == 1) || m < n; m <<= 1) {
      vector<pair<int, int> > suffix(n);
      for (int i = 0; i < n; ++i) {
        sa[i] = i;
        suffix[i] = make_pair(rank[i],
            i + m < n ? rank[i + m] : numeric_limits<int>::min());
      }
      sort(sa.begin(), sa.end(), Indexer<pair<int, int> >(&suffix[0]));
      for (int i = 0; i < n; ++i) {
        if (i == 0 || (suffix[sa[i]] != suffix[sa[i - 1]])) {
          rank[sa[i]] = i;
        } else {
          rank[sa[i]] = rank[sa[i - 1]];
        }
      }
    }

    SuffixArrayBase::init(n, a);
  }
};


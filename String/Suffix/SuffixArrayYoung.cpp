#include "SuffixArrayBase.cpp"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct SuffixArrayYoung: SuffixArrayBase {
  template<typename T>
  void init(int n, const T a[]) {
    sa.resize(n);
    rank.resize(n);

    vector<pair<T, int> > assoc(n);
    for (int i = 0; i < n; ++i) {
      assoc[i] = make_pair(a[i], i);
    }
    sort(assoc.begin(), assoc.end());
    for (int i = 0; i < n; ++i) {
      sa[i] = assoc[i].second;
      if (i == 0 || assoc[i].first != assoc[i - 1].first) {
        rank[sa[i]] = i;
      } else {
        rank[sa[i]] = rank[sa[i - 1]];
      }
    }

    vector<int> tmp(n), cnt(n);
    vector<pair<int, int> > suffix(n);
    for (int m = 1; m < n; m <<= 1) {
      // snd
      for (int i = 0; i < m; ++i) {
        tmp[i] = n - m + i;
      }
      for (int i = 0, j = m; i < n; ++i) {
        if (sa[i] >= m) {
          tmp[j++] = sa[i] - m;
        }
      }
      // fst
      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < n; ++i) {
        ++cnt[rank[i]];
      }
      partial_sum(cnt.begin(), cnt.end(), cnt.begin());
      for (int i = n - 1; i >= 0; --i) {
        sa[--cnt[rank[tmp[i]]]] = tmp[i];
      }
      //
      for (int i = 0; i < n; ++i) {
        suffix[i] = make_pair(rank[i],
          i + m < n ? rank[i + m] : numeric_limits<int>::min());
      }
      for (int i = 0; i < n; ++i) {
        if (i == 0 || suffix[sa[i]] != suffix[sa[i - 1]]) {
          rank[sa[i]] = i;
        } else {
          rank[sa[i]] = rank[sa[i - 1]];
        }
      }
    }

    SuffixArrayBase::init(n, a);
  }
};


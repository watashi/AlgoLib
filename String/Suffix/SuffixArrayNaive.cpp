#pragma once
#include "SuffixArrayBase.cpp"
#include <algorithm>

using namespace std;

struct SuffixArrayNaive: SuffixArrayBase {
  template<typename T>
  void init(int n, const T a[]) {
    sa.clear();
    for (int i = 0; i < n; ++i) {
      sa.push_back(i);
    }
    sort(sa.begin(), sa.end(), [=](int i, int j) {
        return lexicographical_compare(a + i, a + n, a + j, a + n);
      });

    rank.resize(n);
    for (int i = 0; i < n; ++i) {
      rank[sa[i]] = i;
    }

    height.resize(n);
    if (n > 0) {
      height[0] = 0;
    }
    for (int i = 1; i < n; ++i) {
      int h = n - max(sa[i], sa[i - 1]);
      height[i] = mismatch(a + sa[i], a + sa[i] + h, a + sa[i - 1]).first - (a + sa[i]);
    }
  }
};

#pragma once

#include <vector>

using namespace std;

struct SuffixArrayBase {
  vector<int> sa, rank, height;

  template<typename T>
  void init(int n, const T a[]) {
    height.resize(n);
    for (int i = 0, z = 0; i < n; ++i) {
      if (rank[i] == 0) {
        height[0] = z = 0;
      } else {
        int x = i, y = sa[rank[i] - 1];
        z = max(0, z - 1);
        while (x + z < n && y + z < n && a[x + z] == a[y + z]) {
          ++z;
        }
        height[rank[i]] = z;
      }
    }
  }
};

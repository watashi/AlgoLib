#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T = char>
struct Z {
  vector<T> pat;
  vector<int> z;

  void init(int n, const T s[]) {
    vector<T>(s, s + n).swap(pat);
    z.resize(n);
    if (n > 0) {
      z[0] = n;
    }
    if (n > 1) {
      z[1] = 0;
      for (int& w = z[1]; w + 1 < n && pat[w + 1] == pat[w]; ++w) {
      }
    }
    for (int i = 2, k = 1; i < n; ++i) {
      int x = k + z[k] - i, y = z[i - k];
      if (y < x) {
        z[i] = y;
      } else {
        z[i] = max(0, x);
        for (int& w = z[i]; w + i < n && pat[w + i] == pat[w]; ++w) {
        }
        k = i;
      }
    }
  }

  vector<int> gao(int m, const T t[]) {
    int n = (int)pat.size();
    vector<int> ret(m);
    if (m > 0) {
      for (int& w = ret[0]; w < n && w < m && t[w] == pat[w]; ++w) {
      }
    }
    for (int i = 1, k = 0; i < m; ++i) {
      int x = k + ret[k] - i, y = i - k < n ? z[i - k] : 0;
      if (y < x) {
        ret[i] = y;
      } else {
        ret[i] = max(0, x);
        for (int& w = ret[i]; w < n && w + i < m && t[w + i] == pat[w]; ++w) {
        }
        k = i;
      }
    }
    return ret;
  }
};


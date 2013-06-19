#include <vector>

using namespace std;

template<typename T = char>
struct KMP {
  vector<T> pat;
  vector<int> fail;

  void init(int n, const T s[]) {
    vector<T>(s, s + n).swap(pat);
    fail.resize(n);
    if (n > 0) {
      fail[0] = -1;
    }
    for (int i = 1; i < n; ++i) {
      int k = fail[i - 1];
      while (k >= 0 && pat[k + 1] != pat[i]) {
        k = fail[k];
      }
      fail[i] = (pat[k + 1] == pat[i]) ? k + 1 : -1;
    }
  }

  vector<int> gao(int m, const T t[]) {
    if (pat.empty()) {
      return vector<int>(m, 0);
    }
    vector<int> ret(m);
    for (int i = 0, k = 0; i < m; ) {
      if (t[i] == pat[k]) {
        ++k;
        ret[i++] = k;
        if (k == (int)pat.size()) {
          k = fail[k - 1] + 1;
        }
      } else if (k > 0) {
        k = fail[k - 1] + 1;
      } else {
        ret[i++] = 0;
      }
    }
    return ret;
  }
};

#include <algorithm>

using namespace std;

struct Manacher {
  vector<int> p;

  template<typename T>
  void init(int n, const T s[]) {
    p.resize(max(0, 2 * n - 1));
    for (int i = 0, j = 0, k = 0; i <= 2 * (n - 1); ++i) {
      int d = i < k ? min(p[j + j - i], (k - i) / 2) : 0;
      int a = i / 2 - d, b = (i + 1) / 2 + d;
      while (0 <= a && b < n && s[a] == s[b]) {
        --a;
        ++b;
        ++d;
      }
      p[i] = d;
      if (k < 2 * b - 1) {
        j = i;
        k = 2 * b - 1;
      }
    }
  }
};

// brute-force
struct Palindrome {
  vector<int> p;

  template<typename T>
  void init(int n, const T s[]) {
    p.resize(max(0, 2 * n - 1));
    for (int i = 0; i < (int)p.size(); ++i) {
      int a = i / 2, b = (i + 1) / 2, d = 0;
      while (0 <= a && b < n && s[a] == s[b]) {
        --a;
        ++b;
        ++d;
      }
      p[i] = d;
    }
  }
};

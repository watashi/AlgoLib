#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXM = 16;
const int MAXN = 1 << MAXM;

// LCA
struct LCA {
  vector<int> e[MAXN];
  int d[MAXN], p[MAXN][MAXM];

  void dfs_(int v, int f) {
    p[v][0] = f;
    for (int i = 1; i < MAXM; ++i) {
      p[v][i] = p[p[v][i - 1]][i - 1];
    }
    for (int i = 0; i < (int)e[v].size(); ++i) {
      int w = e[v][i];
      if (w != f) {
        d[w] = d[v] + 1;
        dfs_(w, v);
      }
    }
  }

  int up_(int v, int m) {
    for (int i = 0; i < MAXM; ++i) {
      if (m & (1 << i)) {
        v = p[v][i];
      }
    }
    return v;
  }

  int lca(int a, int b) {
    if (d[a] > d[b]) {
      swap(a, b);
    }
    b = up_(b, d[b] - d[a]);
    if (a == b) {
      return a;
    } else {
      for (int i = MAXM - 1; i >= 0; --i) {
        if (p[a][i] != p[b][i]) {
          a = p[a][i];
          b = p[b][i];
        }
      }
      return p[a][0];
    }
  }

  void init(int n) {
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add(int a, int b) {
    e[a].push_back(b);
    e[b].push_back(a);
  }

  void build() {
    d[0] = 0;
    dfs_(0, 0);
  }
} lca;


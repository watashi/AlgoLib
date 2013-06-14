#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<int MAXN>
struct Tarjan {
  int n;
  vector<int> e[MAXN];

  vector<int> cut;
  vector<pair<int, int> > bridge;
  vector<vector<pair<int, int> > > bcc;

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add(int a, int b) {
    // assert(find(a.begin(), a.end(), b) == a.end());
    e[a].push_back(b);
    e[b].push_back(a);
  }

  int dfn[MAXN], low[MAXN];
  int timestamp;
  stack<pair<int, int> > s;

  void dfs(int v, int p) {
    int part = p == -1 ? 0 : 1;
    dfn[v] = low[v] = timestamp++;
    for (vector<int>::const_iterator w = e[v].begin(); w != e[v].end(); ++w) {
      pair<int, int> f = make_pair(min(v, *w), max(v, *w));
      if (dfn[*w] == -1) {
        s.push(f);
        dfs(*w, v);
        low[v] = min(low[v], low[*w]);
        if (dfn[v] <= low[*w]) {
          // articulation point
          if (++part == 2) {
            cut.push_back(v);
          }
          // articulation edge
          if (dfn[v] < low[*w]) {
            bridge.push_back(f);
          }
          // biconnected component (2-vertex-connected)
          vector<pair<int, int> > t;
          do {
            t.push_back(s.top());
            s.pop();
          } while (t.back() != f);
          bcc.push_back(t);
        }
      } else if (*w != p && dfn[*w] < dfn[v]) {
        s.push(f);
        low[v] = min(low[v], dfn[*w]);
      }
    }
  }

  void gao() {
    cut.clear();
    bridge.clear();
    bcc.clear();

    timestamp = 0;
    stack<pair<int, int> >().swap(s);
    fill(dfn, dfn + n, -1);

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i, -1);
      }
    }
  }
};


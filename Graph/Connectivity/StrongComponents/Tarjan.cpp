#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

template<int MAXN>
struct SCC {
  int n;
  vector<int> e[MAXN];

  int id[MAXN];
  vector<vector<int> > scc;

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add(int a, int b) {
    // assert(find(a.begin(), a.end(), b) == a.end());
    e[a].push_back(b);
  }

  int dfn[MAXN], low[MAXN];
  int timestamp;
  stack<int> s;

  void dfs(int v) {
    dfn[v] = timestamp++;
    low[v] = dfn[v];
    s.push(v);
    for (vector<int>::const_iterator w = e[v].begin(); w != e[v].end(); ++w) {
      if (dfn[*w] == -1) {
        dfs(*w);
        low[v] = min(low[v], low[*w]);
      } else if (dfn[*w] != -2) {
        low[v] = min(low[v], dfn[*w]);
      }
    }

    if (low[v] == dfn[v]) {
      vector<int> t;
      do {
        int w = s.top();
        s.pop();
        id[w] = (int)scc.size();
        t.push_back(w);
        dfn[w] = -2;
      } while (t.back() != v);
      scc.push_back(t);
    }
  }

  int gao() {
    scc.clear();
    stack<int>().swap(s);
    timestamp = 0;
    fill(dfn, dfn + n, -1);

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
    return (int)scc.size();
  }
};


#include <vector>
#include <algorithm>

using namespace std;

struct SCCKosaraju {
  int n;
  vector<vector<int> > e, re;

  vector<int> id;
  vector<vector<int> > scc;

  void init(int n) {
    this->n = n;
    vector<vector<int> >(n).swap(e);
    vector<vector<int> >(n).swap(re);
    id.resize(n);
  }

  void add(int a, int b) {
    e[a].push_back(b);
    re[b].push_back(a);
  }

  vector<int> todo;

  void dfs(int v) {
    id[v] = v;
    for (vector<int>::const_iterator w = e[v].begin(); w != e[v].end(); ++w) {
      if (id[*w] == -1) {
        dfs(*w);
      }
    }
    todo.push_back(v);
  }

  void rdfs(int v) {
    id[v] = (int)scc.size() - 1;
    scc.back().push_back(v);
    for (vector<int>::const_iterator w = re[v].begin(); w != re[v].end(); ++w) {
      if (id[*w] == -1) {
        rdfs(*w);
      }
    }
  }

  int gao() {
    todo.clear();
    fill(id.begin(), id.end(), -1);
    for (int i = 0; i < n; ++i) {
      if (id[i] == -1) {
        dfs(i);
      }
    }

    scc.clear();
    reverse(todo.begin(), todo.end());
    fill(id.begin(), id.end(), -1);
    for (int i = 0; i < n; ++i) {
      if (id[todo[i]] == -1) {
        scc.push_back(vector<int>());
        rdfs(todo[i]);
      }
    }

    return (int)scc.size();
  }
};


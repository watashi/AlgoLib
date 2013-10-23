#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct HopcroftKarp {
  int nx, ny;
  vector<int> mx, my;
  vector<vector<int> > e;

  void init(int nx, int ny) {
    this->nx = nx;
    this->ny = ny;
    mx.resize(nx);
    my.resize(ny);
    e.clear();
    e.resize(nx);
    d.resize(nx);
  }

  void add(int a, int b) {
    e[a].push_back(b);
  }

  vector<int> d;

  int bfs() {
    bool ret = false;
    queue<int> q;

    for (int i = 0; i < nx; ++i) {
      if (mx[i] == -1) {
        d[i] = 0;
        q.push(i);
      } else {
        d[i] = -1;
      }
    }

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int w: e[v]) {
        if (my[w] == -1) {
          ret = true;
        } else if (d[my[w]] == -1) {
          d[my[w]] = d[v] + 1;
          q.push(my[w]);
        }
      }
    }

    return ret;
  }

  bool dfs(int v) {
    for (int w: e[v]) {
      if (my[w] == -1 || (d[my[w]] == d[v] + 1 && dfs(my[w]))) {
        mx[v] = w;
        my[w] = v;
        return true;
      }
    }
    d[v] = -1;
    return false;
  }

  int gao() {
    int ret = 0;
    fill(mx.begin(), mx.end(), -1);
    fill(my.begin(), my.end(), -1);
    while (bfs()) {
      for (int i = 0; i < nx; ++i) {
        if (mx[i] == -1 && dfs(i)) {
          ++ret;
        }
      }
    }
    return ret;
  }
};

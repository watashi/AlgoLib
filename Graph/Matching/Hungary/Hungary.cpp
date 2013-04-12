// Maximum matchings in bipartite graphs

#include <algorithm>

using namespace std;

template<int MAXX, int MAXY>
struct Hungary {
  int nx, ny, mx[MAXX], my[MAXY];
  vector<int> e[MAXX];

  bool mark[MAXX];

  void init(int nx, int ny) {
    this->nx = nx;
    this->ny = ny;
    for (int i = 0; i < nx; ++i) {
      e[i].clear();
    }
  }

  void add(int a, int b) {
    e[a].push_back(b);
  }

  bool augment(int i) {
    if (!mark[i]) {
      mark[i] = true;
      for (vector<int>::const_iterator j = e[i].begin(); j != e[i].end(); ++j) {
        if (my[*j] == -1 || augment(my[*j])) {
          mx[i] = *j;
          my[*j] = i;
          return true;
        }
      }
    }
    return false;
  }

  int gao() {
    int ret = 0;
    fill(mx, mx + nx, -1);
    fill(my, my + ny, -1);
    for (int i = 0; i < nx; ++i) {
      fill(mark, mark + nx, false);
      if (augment(i)) {
        ++ret;
      }
    }
    return ret;
  }
};

Hungary<1024, 1024> h;

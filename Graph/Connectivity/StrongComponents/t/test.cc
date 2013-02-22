#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace boost;

#ifdef KOSARAJU
#include "../Kosaraju.cpp"
#else
#include "../Tarjan.cpp"
#endif

const int MAXN = 100100;
const int MAXM = 500000;

int id[MAXN];
SCC<MAXN> scc;

template<typename T>
T normalize(T v) {
  return v;
}

template<typename T>
vector<T> normalize(vector<T> v) {
  for (T& i: v) {
    i = normalize(i);
  }
  sort(v.begin(), v.end());
  return v;
}

int main() {
  for (int ri = 1; ri <= 10; ++ri) {
    adjacency_list<vecS, vecS, directedS> g;

    scc.init(MAXN);
    for (int i = 0; i < MAXM; ++i) {
      int a = i < MAXN ? i : rand() % MAXN;
      int b = rand() % MAXN;
      if (a != b) {
        scc.add(a, b);
        add_edge(a, b, g);
      }
    }
    scc.gao();

    int n = strong_components(g, id);
    printf("%d %d\n", n, scc.gao());
    vector<vector<int> > v(n), w(scc.scc);
    for (int i = 0; i < MAXN; ++i) {
      // printf("%d %d\n", scc.id[i], id[i]);
      v[id[i]].push_back(i);
    }
    assert(normalize(v) == normalize(w));
  }

  return 0;
}


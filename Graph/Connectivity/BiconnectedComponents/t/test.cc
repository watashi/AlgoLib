#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace std;

#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;

#include "../Tarjan.cpp"

const int MAXN = 100100;
const int MAXM = 500000;

Tarjan<MAXN> tarjan;

template<typename T>
T normalize(T v) {
  return v;
}

template<typename T>
pair<T, T> normalize(pair<T, T> v) {
  if (v.first > v.second) {
    swap(v.first, v.second);
  }
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

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property, property<edge_index_t, int> > graph_t;

int main() {
  static int comp[MAXM];

  for (int ri = 1; ri <= 100; ++ri) {
    int n = 1 + rand() % MAXN;
    int m = 1 + rand() % MAXM;
    map<pair<int, int>, int> mp;
    graph_t g;

    printf("#%d: n = %d, m = %d\n", ri, n, m);
    tarjan.init(n);
    for (int i = 0; i < m; ++i) {
      int a = rand() % n;
      int b = rand() % n;
      pair<int, int> e = {min(a, b), max(a, b)};
      if (a != b && mp.count(e) == 0) {
        mp[e] = i;
        tarjan.add(a, b);
        add_edge(a, b, i, g);
      }
    }
    tarjan.gao();

    vector<int> cut;
    articulation_points(g, back_inserter(cut));
    printf("cut: %d == %d\n", cut.size(), tarjan.cut.size());
    assert(normalize(cut) == normalize(tarjan.cut));

    int num_comps = biconnected_components(g,
      make_iterator_property_map(comp, get(edge_index, g)));
    printf("bcc: %d == %d\n", num_comps, tarjan.bcc.size());
    vector<vector<pair<int, int> > > bcc(num_comps);
    for (auto i: mp) {
      bcc[comp[i.second]].push_back(i.first);
    }
    assert(normalize(bcc) == normalize(tarjan.bcc));
  }

  return 0;
}


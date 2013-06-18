#include "../Tarjan.cpp"
#include "common.h"

#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property, property<edge_index_t, int> > graph_t;

class BCCTarjanTest: public ::testing::TestWithParam<pair<int, int> > {
  protected:
    static const int MAXN = 100100;
    static Tarjan tarjan;
};

Tarjan BCCTarjanTest::tarjan;

TEST_P(BCCTarjanTest, Random) {
  int n, m;
  graph_t g;
  set<pair<int, int> > st;
  vector<pair<int, int> > e;

  tie(n, m) = GetParam();
  srand(n ^ m);
  tarjan.init(n);
  for (int i = 0; i < m; ++i) {
    int a = rand() % n;
    int b = rand() % n;
    if (a > b) {
      swap(a, b);
    }
    if (a != b && st.insert({a, b}).second) {
      e.push_back({a, b});
      if (rand() % 2 == 0) {
        swap(a, b);
      }
      tarjan.add(a, b);
      add_edge(a, b, (int)e.size() - 1, g);
    }
  }
  m = (int)e.size();
  tarjan.gao();

  vector<int> cut;
  articulation_points(g, back_inserter(cut));
  ASSERT_EQ(normalize(cut), normalize(tarjan.cut)) << "articulation points";

  vector<int> comp(m);
  int ncomp = biconnected_components(g,
    make_iterator_property_map(comp.begin(), get(edge_index, g)));
  ASSERT_EQ(ncomp, tarjan.bcc.size()) << "number of biconnected components";

  vector<vector<pair<int, int> > > bcc(ncomp);
  for (int i = 0; i < m; ++i) {
    bcc[comp[i]].push_back(e[i]);
  }
  ASSERT_EQ(normalize(bcc), normalize(tarjan.bcc)) << "biconnected components";
}

static vector<pair<int, int> > params = {
  {10, 20}, {10, 30}, {10, 50}, {10, 70}, {10, 100},
  {20, 20}, {20, 30}, {20, 50}, {20, 70}, {20, 100},
  {30, 20}, {30, 30}, {30, 50}, {30, 70}, {30, 100},
  {   100,    500},
  {  1000,   5000},
  { 10000,  50000},
  {100000, 500000},
};

INSTANTIATE_TEST_CASE_P(, BCCTarjanTest, ::testing::ValuesIn(params));

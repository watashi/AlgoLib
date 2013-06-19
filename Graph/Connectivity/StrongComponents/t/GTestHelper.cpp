#include "common.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace boost;

#define SCCTest CONCAT_EX(SCC, Test)

class SCCTest: public ::testing::TestWithParam<pair<int, int> > {
  protected:
    static const int MAXN = 100100;
    static SCC scc;
};

SCC SCCTest::scc;

TEST_P_EX(SCCTest, Random) {
  int n, m;
  adjacency_list<vecS, vecS, directedS> g;

  tie(n, m) = GetParam();
  srand(n ^ m);
  scc.init(n);
  for (int i = 0; i < m; ++i) {
    int a = rand() % n;
    int b = rand() % n;
    scc.add(a, b);
    add_edge(a, b, g);
  }
  for (int i = 0; i < n; ++i) {
    if (scc.e[i].empty()) {
      int a = i;
      int b = rand() % n;
      scc.add(a, b);
      add_edge(a, b, g);
    }
  }
  scc.gao();

  vector_property_map<int> id(n);
  int ncomp = strong_components(g, id);
  ASSERT_EQ(ncomp, scc.scc.size()) << "number of strong components";

  vector<vector<int> > v(ncomp);
  for (int i = 0; i < n; ++i) {
    v[id[i]].push_back(i);
  }
  ASSERT_EQ(normalize(v), normalize(scc.scc)) << "strong components";
}

static const vector<pair<int, int> > params = {
  {10, 20}, {10, 30}, {10, 50}, {10, 70}, {10, 110},
  {20, 20}, {20, 30}, {20, 50}, {20, 70}, {20, 110},
  {30, 20}, {30, 30}, {30, 50}, {30, 70}, {30, 110},
  {   100,    1000},
  {  1000,   10000},
  { 10000,  100000},
  {100000, 1000000}
};

INSTANTIATE_TEST_CASE_P_EX(, SCCTest, ::testing::ValuesIn(params));

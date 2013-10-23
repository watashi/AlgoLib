#include "common.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace boost;

#define BMTest CONCAT_EX(BM, Test)

class BMTest: public ::testing::TestWithParam<int> {
  protected:
    static const int MAXN = 5050;
    static BM bm;
};

BM BMTest::bm;

using graph_t = adjacency_list<vecS, vecS, undirectedS>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;
using mate_map_t = vector_property_map<vertex_t>;
using vertex_index_map_t = property_map<graph_t, vertex_index_t>::type;

static bool verify_matching(const graph_t& g, mate_map_t mate) {
  return maximum_cardinality_matching_verifier<
      graph_t, mate_map_t, vertex_index_map_t>::verify_matching(
          g, mate, get(vertex_index, g));
}

TEST_P_EX(BMTest, Random) {
  srand(GetParam());

  int x = rand(1, MAXN);
  int y = rand(1, MAXN);
  int n = x + y;
  int m = n + rand(1, n) * rand(0, 5);
  int ret = 0;
  graph_t g;

  bm.init(x, y);
  for (int i = 0; i < m; ++i) {
    int a = rand(x), b = rand(y);
    if (i < x) {
      a = i;
    } else if (i - x < y) {
      b = i - x;
    }
    bm.add(a, b);
    add_edge(a, x + b, g);
  }
  ret = bm.gao();
  // printf("x=%d, y=%d, m=%d, ans=%d\n", x, y, m, ret);

  mate_map_t mate(n);
  bool success = checked_edmonds_maximum_cardinality_matching(g, mate);
  int ans = matching_size(g, mate);
  auto null = graph_traits<graph_t>::null_vertex;
  ASSERT_EQ(ans, ret) << "matching size";

  for (int i = 0; i < x; ++i) {
    mate[i] = bm.mx[i] == -1 ? null() : x + bm.mx[i];
  }
  for (int i = 0; i < y; ++i) {
    mate[x + i] = bm.my[i] == -1 ? null() : bm.my[i];
  }
  success = verify_matching(g, mate);
  ASSERT_TRUE(success) << "not a maximum cardinality matching";
}

INSTANTIATE_TEST_CASE_P_EX(, BMTest, ::testing::Range(0, 20));

#include "common.h"

// #include <boost/pending/disjoint_sets.hpp>
#include <boost/graph/incremental_components.hpp>

using namespace boost;

#define DISJOINT_SET_TEST CONCAT_EX(DISJOINT_SET, Test)

class DISJOINT_SET_TEST: public ::testing::TestWithParam<int> {
public:
  static const int MAXN = 1 << 20;

protected:
  struct Query {
    int op, a, b;
  };

  void test(int n, const vector<Query>& q) {
    disjoint_sets_with_storage<> ds2(n);

    ds.init(n);
    for (auto i: q) {
      switch (i.op) {
      case 0:
        ASSERT_EQ(ds.getp(i.a) == ds.getp(i.b),
          ds2.find_set(i.a) == ds2.find_set(i.b));
        break;
      case 1:
        ASSERT_EQ(ds.setp(i.a, i.b),
          ds2.find_set(i.a) != ds2.find_set(i.b));
        ds2.union_set(i.a, i.b);
        break;
      }
    }
  }

  static DISJOINT_SET ds;
};

DISJOINT_SET DISJOINT_SET_TEST::ds;

TEST_F_EX(DISJOINT_SET_TEST, FriendOnlyExample) {
  int n = 5;
  vector<Query> q = {
    {1, 1, 1}, {0, 1, 2},
    // (1, 2)
    {1, 1, 2}, {0, 1, 2}, {0, 1, 0},
    // (1, 2, 3)
    {1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 0, 3},
    // (1, 2, 3), (0, 4)
    {1, 0, 4}, {0, 0, 1}, {0, 3, 4}, {0, 1, 4},
    // (0, 1, 2, 3, 4)
    {1, 2, 4}, {0, 0, 1}, {0, 3, 4}, {0, 1, 4},
  };
  test(n, q);
}

TEST_P_EX(DISJOINT_SET_TEST, FriendOnlyRandom) {
  int n = GetParam();
  srand(n);
  int m = n * rand(2, 5);
  vector<Query> q;
  for (int i = 0; i < m; ++i) {
    int a = rand(n);
    int b = rand(n);
    if (rand(3) == 0) {
      q.push_back({1, a, b});
      q.push_back({0, a, rand(n)});
      q.push_back({0, b, rand(n)});
    } else {
      q.push_back({0, a, b});
    }
  }
  test(n, q);
}

INSTANTIATE_TEST_CASE_P_EX(, DISJOINT_SET_TEST,
  ::testing::Values(10, 100, 1000, 10000, 100000, DISJOINT_SET_TEST::MAXN));

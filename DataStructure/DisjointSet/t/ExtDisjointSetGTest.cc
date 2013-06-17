#include "../ExtDisjointSet.cpp"
#define DISJOINT_SET ExtDisjointSet
#include "GTestHelper.cpp"

TEST_F(ExtDisjointSetTest, FriendEnemyExample) {
  const int n = 11;
  ExtDisjointSet ds;
  auto r = ExtDisjointSet::RE;
  auto setp = [&ds](int i, int j){
    if (rand(2) == 0) {
      swap(i, j);
    }
    return ds.setp(i, j);
  };

  srand(0);
  ds.init(n);
  for (int i = 0; i < n; ++i) {
    // self
    ASSERT_EQ(-1, setp(i, r(i)));
    ASSERT_TRUE(ds.getp(i) == r(ds.getp(r(i))));
    if ((i ^ 1) < n) {
      // enemy
      ASSERT_EQ(1 - i % 2, setp(i, r(i ^ 1)));
      ASSERT_TRUE(ds.getp(i) == r(ds.getp(i ^ 1)));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (i % 2 == j % 2) {
        // friend
        ASSERT_NE(-1, ds.setp(i, j));
      }
    }
  }
  // test
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i % 2 == j % 2) {
        ASSERT_TRUE(ds.getp(i) == ds.getp(j));
      } else {
        ASSERT_TRUE(ds.getp(i) == r(ds.getp(j)));
      }
    }
  }
  // size
  int root = ds.getp(0);
  root = root < 0 ? r(root) : root;
  ASSERT_EQ(root % 2 == 0 ? 6 : 5, ds.s[root]);
  ASSERT_EQ(root % 2 == 0 ? 5 : 6, ds.t[root]);
}


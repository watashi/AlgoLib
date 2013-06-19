#ifndef _SUFFIX_ARRAY_GTEST_HELPER
#define _SUFFIX_ARRAY_GTEST_HELPER

#include "common.h"
#include "../../t/GTestHelper.cpp"
#include "../SuffixArrayNaive.cpp"

#ifndef SUFFIX_ARRAY_NAIVE
#define SUFFIX_ARRAY_NAIVE SuffixArrayNaive
#endif

#define SMALL_TEST CONCAT_EX(SUFFIX_ARRAY, SmallTest)
#define LARGE_TEST CONCAT_EX(SUFFIX_ARRAY, LargeTest)

class SMALL_TEST: public ::testing::TestWithParam<string> {
};

class LARGE_TEST: public ::testing::TestWithParam<int> {
};

static inline void test(const string& s) {
  static SUFFIX_ARRAY sa;
  static SUFFIX_ARRAY_NAIVE san;

  sa.init(s.size(), s.data());
  san.init(s.size(), s.data());
  ASSERT_EQ(san.sa, sa.sa);
  ASSERT_EQ(san.rank, sa.rank);
  ASSERT_EQ(san.height, sa.height);
}

TEST(CONCAT_EX(SUFFIX_ARRAY, Test), Example) {
  wstring a = L"abracadabra";
  vector<int> s = {10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2};
  vector<int> r = {2, 6, 10, 3, 7, 4, 8, 1, 5, 9, 0};
  vector<int> h = {0, 1, 4, 1, 1, 0, 3, 0, 0, 0, 2};
  SUFFIX_ARRAY sa;

  sa.init(a.size(), a.data());
  ASSERT_EQ(s, sa.sa);
  ASSERT_EQ(r, sa.rank);
  ASSERT_EQ(h, sa.height);
}

TEST_P_EX(SMALL_TEST, Biolerplate) {
  test(GetParam());
}

TEST_P_EX(LARGE_TEST, Random) {
  test(randstr(GetParam()));
}

INSTANTIATE_TEST_CASE_P_EX(, SMALL_TEST, ::testing::ValuesIn(biolerplate));

INSTANTIATE_TEST_CASE_P_EX(, LARGE_TEST, ::testing::Range(0, 10));

#endif

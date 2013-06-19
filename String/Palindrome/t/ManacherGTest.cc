#include "../Manacher.cpp"
#include "common.h"
#include "../../t/GTestHelper.cpp"

class ManacherSmallTest: public ::testing::TestWithParam<string> {
};

class ManacherLargeTest: public ::testing::TestWithParam<int> {
};

static Manacher manacher;
static Palindrome palindrome;

TEST(ManacherTest, Example) {
  vector<int> v = {-1, -2, -1, -1, -3, -1, -1, -2};
  vector<int> p = {1, 0, 2, 0, 1, 1, 1, 0, 4, 0, 1, 1, 1, 0, 1};
  manacher.init(v.size(), v.data());
  ASSERT_EQ(p, manacher.p);
}

TEST_P(ManacherSmallTest, Biolerplate) {
  string s = GetParam();
  manacher.init(s.length(), s.c_str());
  palindrome.init(s.length(), s.c_str());
  ASSERT_EQ(palindrome.p, manacher.p);
}

TEST_P(ManacherLargeTest, Random) {
  string s = randstr(GetParam());
  manacher.init(s.length(), s.c_str());
  palindrome.init(s.length(), s.c_str());
  ASSERT_EQ(palindrome.p, manacher.p);
}

INSTANTIATE_TEST_CASE_P(, ManacherSmallTest, ::testing::ValuesIn(biolerplate));

INSTANTIATE_TEST_CASE_P(, ManacherLargeTest, ::testing::Range(0, 10));

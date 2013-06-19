#include "../Z.cpp"
#include "common.h"
#include "../../t/GTestHelper.cpp"

#include <algorithm>

using namespace std;

static vector<int> zfunc(const string& s) {
  vector<int> ret;
  for (string::const_iterator i = s.begin(); i != s.end(); ++i) {
    ret.push_back(mismatch(i, s.end(), s.begin()).first - i);
  }
  return ret;
}

static vector<int> match(const string& s, const string& t) {
  vector<int> ret;
  for (string::const_iterator i = s.begin(); i != s.end(); ++i) {
    ret.push_back(mismatch(i, min(i + t.size(), s.end()), t.begin()).first - i);
  }
  return ret;
}

static Z<char> z;

class ZSmallTest: public ::testing::TestWithParam<pair<string, string> > {
};

class ZLargeTest: public ::testing::TestWithParam<int> {
};

TEST(ZTest, Example) {
  vector<string> str = {
    "fa", "mi", "fa", "mi", "fa", "mi", "ma",
    "fa", "mi", "fa", "mi", "ma", "~"};
  vector<string> pat = {"fa", "mi", "fa", "mi", "ma"};
  vector<int> zfunc = {5, 0, 2, 0, 0};
  vector<int> match = {4, 0, 5, 0, 2, 0, 0, 5, 0, 2, 0, 0, 0};
  Z<string> z;

  z.init(pat.size(), pat.data());
  ASSERT_EQ(zfunc, z.z);
  ASSERT_EQ(match, z.gao(str.size(), str.data()));
}

TEST_P(ZSmallTest, Biolerplate) {
  string str, pat;
  tie(str, pat) = GetParam();
  z.init(pat.length(), pat.c_str());
  ASSERT_EQ(zfunc(pat), z.z);
  ASSERT_EQ(match(str, pat), z.gao(str.length(), str.c_str()));
}

TEST_P(ZLargeTest, Random) {
  int param = GetParam();
  string str = randstr(param), pat;

  srand(param);
  pat = str;
  pat = pat.substr(0, rand(pat.length()));
  pat = pat.substr(rand(pat.length()));

  z.init(pat.length(), pat.c_str());
  ASSERT_EQ(zfunc(pat), z.z);
  ASSERT_EQ(match(str, pat), z.gao(str.length(), str.c_str()));
}

INSTANTIATE_TEST_CASE_P(, ZSmallTest, ::testing::ValuesIn(biolerplate2));

INSTANTIATE_TEST_CASE_P(, ZLargeTest, ::testing::Range(0, 10));

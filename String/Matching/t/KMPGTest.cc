#include "../KMP.cpp"
#include "common.h"
#include "../../t/GTestHelper.cpp"

#include <algorithm>

using namespace std;

static vector<int> fail(const string& s) {
  vector<int> ret(s.length());
  for (int i = 0; i < (int)s.length(); ++i) {
    for (int j = 1; ; ++j) {
      if (equal(s.c_str() + j, s.c_str() + i + 1, s.c_str())) {
        ret[i] = i - j;
        break;
      }
    }
  }
  return ret;
}

static vector<int> match(const string& s, const string& t) {
  vector<int> ret(s.length());
  for (int i = 0; i < (int)s.length(); ++i) {
    for (int j = min((int)t.length(), i + 1); j >= 0; --j) {
      if (equal(t.c_str(), t.c_str() + j, s.c_str() + i + 1 - j)) {
        ret[i] = j;
        break;
      }
    }
  }
  return ret;
}

static KMP<char> kmp;

class KMPSmallTest: public ::testing::TestWithParam<pair<string, string> > {
};

class KMPLargeTest: public ::testing::TestWithParam<int> {
};

TEST(KMPTest, Example) {
  vector<string> str = {
    "fa", "mi", "fa", "mi", "fa", "mi", "ma",
    "fa", "mi", "fa", "mi", "ma", "~"};
  vector<string> pat = {"fa", "mi", "fa", "mi", "ma"};
  vector<int> fail = {-1, -1, 0, 1, -1};
  vector<int> match = {1, 2, 3, 4, 3, 4, 5, 1, 2, 3, 4, 5, 0};
  KMP<string> kmp;

  kmp.init(pat.size(), pat.data());
  ASSERT_EQ(fail, kmp.fail);
  ASSERT_EQ(match, kmp.gao(str.size(), str.data()));
}

TEST_P(KMPSmallTest, Biolerplate) {
  string str, pat;
  tie(str, pat) = GetParam();
  kmp.init(pat.length(), pat.c_str());
  ASSERT_EQ(fail(pat), kmp.fail);
  ASSERT_EQ(match(str, pat), kmp.gao(str.length(), str.c_str()));
}

TEST_P(KMPLargeTest, Random) {
  int param = GetParam();
  string str = randstr(param), pat;

  srand(param);
  pat = str;
  pat = pat.substr(0, rand(pat.length()));
  pat = pat.substr(rand(pat.length()));

  kmp.init(pat.length(), pat.c_str());
  ASSERT_EQ(fail(pat), kmp.fail);
  ASSERT_EQ(match(str, pat), kmp.gao(str.length(), str.c_str()));
}

INSTANTIATE_TEST_CASE_P(, KMPSmallTest, ::testing::ValuesIn(biolerplate2));

INSTANTIATE_TEST_CASE_P(, KMPLargeTest, ::testing::Range(0, 10));

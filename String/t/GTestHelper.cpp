#ifndef _STRING_GTEST_HELPER
#define _STRING_GTEST_HELPER

#include <vector>
#include <string>
#include <random>

using namespace std;

static const vector<string> biolerplate = {
  // empty
  "",
  // singleton
  " ",
  "~",
  // short
  "!?",
  "zju",
  "icpc",
  // replicate
  "ooooooooooooooooooo",
  "eeeeeeeeeeeeeeeeeeee",
  // cyclemt19937
  "oxooxooxooxoo",
  "oxooxooxooxoox",
  "oxooxooxooxooxo",
  "ACGTACGTACGTACGTACGTACG",
  "ACGTACGTACGTACGTACGTACGT",
  "010101010101010101010101010101010101010",
  "0101010101010101010101010101010101010101",
  // ordered
  "abcdefghijklmnopqrstuvwxyz",
  "zyxwvutsrqponmlkjihgfedcba",
  // ...
  "ABCCAB",
  "BANANA",
  "ANPANMAN",
  "AABZABZABCZ",
  "ABC ABCDAB ABCDABCDABDE",
  "ABCDABCDABDE ABCDAB ABC",
};

static const vector<pair<string, string> > biolerplate2 = {
  {"", ""},
  {"test", ""},
  {"", "test"},
  {"AABZABZABCZ", "ABZABC"},
  {"oxooxooxooxoo", "ox"},
  {"oxooxooxooxoox", "ooxx"},
  {"ACGTACGTACGTACGTACGTACG", "ACG"},
  {"0101010101010101010101010101010101010101", "10101"},
  {"ABC ABCDAB ABCDABCDABDE", "ABCDABD"},
  {"ABCDABCDABDE ABCDAB ABC", "ABCDABE"},
};

static inline string randstr(int seed, char a = 'A', char b = 'C', int len = 4096) {
  mt19937 rng(seed);
  string ret(1 + rng() % len, a);
  uniform_int_distribution<char> uid(a, b);
  uid.__generate(ret.begin(), ret.end(), rng);
  return ret;
}

#endif

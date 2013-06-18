#include "../RMQ.cpp"
#include "common.h"

#include <random>
#include <vector>
#include <algorithm>

using namespace std;

TEST(RMQTest, Value) {
  const int N = 512;
  mt19937 rng;
  uniform_real_distribution<double> urd;
  RMQ<double> rmq;
  vector<double> v(N);

  urd.__generate(v.begin(), v.end(), rng);
  rmq.init((int)v.size(), &v[0]);
  for (int i = 0; i < N; ++i) {
    double val = v[i];
    for (int j = i; j < N; ++j) {
      val = min(val, v[j]);
      ASSERT_EQ(val, rmq.value(i, j + 1));
    }
  }
}

TEST(RMQTest, Index) {
  const int N = 513;
  mt19937 rng;
  uniform_int_distribution<char> uid('0', '9');
  RMQ<char> rmq;
  string s(N, '\0');

  uid.__generate(s.begin(), s.end(), rng);
  rmq.init((int)s.size(), &s[0]);
  for (int i = 0; i < N; ++i) {
    int idx = i;
    for (int j = i; j < N; ++j) {
      if (s[j] < s[idx]) {
        idx = j;
      }
      ASSERT_EQ(idx, rmq.index(i, j + 1));
    }
  }
}


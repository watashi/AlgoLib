#include "../BIT.cpp"
#include "common.h"

#include <random>

using namespace std;

template<typename T, typename RND>
void test(const int n, const int m, const T a, const T b) {
  static const double EPS = 1e-10;
  BIT<T> bit;
  vector<T> vec(n);
  mt19937_64 rng;
  uniform_int_distribution<int> idx(0, n - 1);
  RND val(a, b);

  bit.init(n);
  for (int k = 0; k < m; ++k) {
    int i = idx(rng);
    T v = val(rng);
    if (k % 2 == 0) {
      vec[i] = v;
      bit.set(i, v);
    } else {
      vec[i] += v;
      bit.add(i, v);
    }

    T sum = 0;
    for (int j = 0; j <= n; ++j) {
      ASSERT_NEAR(sum, bit.sum(j), EPS) << "[" << k << "][" << j << "]";
      if (j < n) {
        ASSERT_NEAR(vec[j], bit.get(j), EPS) << "[" << k << "][" << j << "]";
        sum += vec[j];
      }
    }
  }
}

TEST(BITTest, Int) {
  const int N = 1000;
  const int M = 5000;
  const long long INF = 1LL << 50;
  test<long long, uniform_int_distribution<long long> >(N, M, -INF, INF);
}

TEST(BITTest, Real) {
  const int N = 1024;
  const int M = 4096;
  const double INF = 1000;
  test<double, uniform_real_distribution<double> >(N, M, -INF, INF);
}


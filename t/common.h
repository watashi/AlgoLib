#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "gtest/gtest.h"

using namespace std;

#define CONCAT(a, b) a ## b
#define CONCAT_EX(a, b) CONCAT(a, b)

#define TEST_EX(a, b) TEST(a, b)
#define TEST_F_EX(a, b) TEST_F(a, b)
#define TEST_P_EX(a, b) TEST_P(a, b)
#define INSTANTIATE_TEST_CASE_P_EX(a, b, c) INSTANTIATE_TEST_CASE_P(a, b, c)

inline int rand(int n) {
  return rand() % n;
}

inline int rand(int l, int r) {
  return l + rand(r - l);
}

template<typename T>
T normalize(T v) {
  return v;
}

template<typename T>
vector<T> normalize(vector<T> v) {
  for (T& i: v) {
    i = normalize(i);
  }
  sort(v.begin(), v.end());
  return v;
}

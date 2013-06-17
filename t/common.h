#ifndef _ALOG_LIB_COMMON
#define _ALOG_LIB_COMMON

#include <gtest/gtest.h>

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

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

#endif

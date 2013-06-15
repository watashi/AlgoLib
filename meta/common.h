#ifndef _ALOG_LIB_COMMON
#define _ALOG_LIB_COMMON

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

using namespace std;

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

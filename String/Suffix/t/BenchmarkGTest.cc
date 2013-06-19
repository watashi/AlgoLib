#include "common.h"
#include "../../t/GTestHelper.cpp"
#include "../SuffixArrayNaive.cpp"
#include "../SuffixArraySimple.cpp"
#include "../SuffixArrayYoung.cpp"

static const int LENGTH = 100100;

template<typename T>
void test(const string& data) {
  T sa;
  sa.init(data.size(), data.data());
}

template<typename T>
class SuffixArrayBenchmark: public ::testing::Test {
};

TYPED_TEST_CASE_P(SuffixArrayBenchmark);

TYPED_TEST_P(SuffixArrayBenchmark, Replicate) {
  string data(LENGTH, 'a');
  test<TypeParam>(data);
}

TYPED_TEST_P(SuffixArrayBenchmark, Cycle) {
  string data(LENGTH, 'a');
  for (int i = 1; i < (int)data.size(); i += 2) {
    data[i] = 'b';
  }
  test<TypeParam>(data);
}

TYPED_TEST_P(SuffixArrayBenchmark, SmallCharset) {
  auto data = randstr(0, 'a', 'c', LENGTH);
  test<TypeParam>(data);
}

TYPED_TEST_P(SuffixArrayBenchmark, LargeCharset) {
  auto data = randstr(0, ' ', '~', LENGTH);
  test<TypeParam>(data);
}

REGISTER_TYPED_TEST_CASE_P(SuffixArrayBenchmark,
    Replicate, Cycle, SmallCharset, LargeCharset);

typedef ::testing::Types<SuffixArraySimple, SuffixArrayYoung> SuffixArrayImpl;

INSTANTIATE_TYPED_TEST_CASE_P(, SuffixArrayBenchmark, SuffixArrayImpl);

## SuffixArrayBase.cpp

* Complexity: Naive > Simple > Young > Linear

* LCP:

    sa.init(n, a);
    rmq.init(n, sa.height.data());

    // lcp of a[i..-1] and a[j..-1]
    int lcp(int i, int j) {
      i = sa.rank[i];
      j = sa.rank[j];
      if (i > j) {
        swap(i, j);
      }
      return i < j ? rmq.value(i + 1, j + 1) : (int)sa.rank.size() - i;
    }

#### Wiki

* [Suffix array](http://en.wikipedia.org/wiki/Suffix_array) `sa` / `rank`
* [LCP array](http://en.wikipedia.org/wiki/LCP_array) `height`

## SuffixArrayNaive.cpp

* Complexity: O(n^2lgn) + O(n^2)

## SuffixArraySimple.cpp

* Complexity: O(nlg^2(n)) + O(n)

#### Prob

1. [AOJ2444](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444)

## SuffixArrayYoung.cpp

* Complexity: O(nlgn) + O(n)
* Radix sort

## SuffixArrayLinear.cpp

* Complexity: O(n)


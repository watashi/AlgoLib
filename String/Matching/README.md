## String Matching

## Knuth-Morris-Pratt (KMP.cpp)

* Failure function: longest prefix that matches a proper suffix
* `p[0..fail[i]]` is the longest suffix of `p[0..i]`: -1 for empty

#### Wiki

* [Knuth–Morris–Pratt algorithm](http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)

## Gusfield's Algorithm (Z.cpp)

* Z function: longest common prefix of `s` and `s[i..]`
* `s[0..z(i)-1] = s[i...i+z(i)-1]`, or `s[0, z(i)] = s[i, z(i)]`


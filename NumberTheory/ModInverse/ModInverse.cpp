#include <cmath>

// a * x + b * y = gcd(a, b) >= 0
long long extGcd(long long a, long long b, long long& x, long long& y) {
  if (b == 0) {
    x = a >= 0 ? 1 : -1;
    y = 0;
    return abs(a);
  } else {
    int g = extGcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
  }
}

// ASSUME: gcd(a, m) == 1
long long modInv(long long a, long long m) {
  long long x, y;
  extGcd(a, m, x, y);
  return (x % m + m) % m;
}


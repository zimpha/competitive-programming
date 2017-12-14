// p(n, k) = \frac{2^{n-k}(n+(2^n-1)(k-1))}{(2^n-1)^2}
#include <cstdio>

const int mod = 1e8;

using int64 = long long;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 gcd(int64 a, int64 b) {
  return b ? gcd(b, a % b) : a;
}

int64 M(int64 n, int64 k) {
  int64 g = gcd(n, pow_mod(2, n, n) - 1 + n);
  int64 b = (pow_mod(2, n, g * mod) - 1 + g * mod) % (g * mod) / g;
  int64 a = n / g;
  return pow_mod(2, n - k, mod) * (a + b * (k - 1) % mod) % mod * b % mod * (pow_mod(2, n, mod) - 1 + mod) % mod;
}

int main() {
  printf("%lld\n", M(3, 1));
  printf("%lld\n", M(6, 2));
  printf("%lld\n", M(1e8 + 7, 1e4 + 7));
  return 0;
}

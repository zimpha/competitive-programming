#include <cstdio>
#include <vector>
#include <bitset>

using int64 = long long;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 calc(int64 n, int64 mod) {
  // (2 + sqrt{3}) ^ (2^n) % mod
  if (pow_mod(3, mod / 2, mod) == 1) {
    n = pow_mod(2, n, mod - 1);
  } else {
    n = pow_mod(2, n, mod + 1);
  }
  int64 a = 1, b = 0;
  int64 c = 2, d = 1;
  for (; n; n >>= 1) {
    if (n & 1) {
      int64 u = (a * c + 3 * b * d) % mod;
      int64 v = (a * d + b * c) % mod;
      a = u, b = v;
    }
    int64 u = (c * c + d * d * 3) % mod;
    int64 v = 2 * c * d % mod;
    c = u, d = v;
  }
  return a;
}

int main() {
  int64 n, m;
  scanf("%lld%lld", &n, &m);
  int64 r = calc(n, m) * 2 % m + m - 2;
  printf("%lld\n", r % m);
  return 0;
}

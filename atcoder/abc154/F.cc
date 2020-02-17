#include <cstdio>

const int mod = 1e9 + 7;
const int N = 3e6;

using int64 = long long;

int64 fac[N], ifac[N];

int64 binom(int n, int m) {
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int r1, r2, c1, c2;
  scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= r2 + c2 + 1; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  int64 ret = 0;
  for (int n = r1; n <= r2; ++n) {
    ret += binom(n + c2 + 1, c2) - binom(n + c1, c1 - 1);
  }
  ret %= mod; ret += mod; ret %= mod;
  printf("%lld\n", ret);
  return 0;
}

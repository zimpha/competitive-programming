#include <cstdio>
#include <cstdio>

using int64 = long long;

const int N = 1e7 + 10, mod = 1e9 + 7;

int64 fac[N], inv[N], a[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 binom(int n, int m) {
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
  int n;
  scanf("%d", &n);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
  }
  inv[n] = pow_mod(fac[n], mod - 2);
  for (int i = n; i >= 1; --i) {
    inv[i - 1] = inv[i] * i % mod;
  }
  a[0] = 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = (2 * i * a[i - 1] % mod - int64(i - 1) * (i - 1) % mod * a[i - 2] % mod + mod) % mod;
  }
  int64 ret = 0;
  for (int i = 0; i <= n; ++i) {
    ret += (i & 1 ? mod - 1 : 1) * binom(n, i) % mod * binom(n, i) % mod * fac[i] % mod * a[n - i] % mod * a[n - i] % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

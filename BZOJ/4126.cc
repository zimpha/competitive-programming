#include <cstdio>
#include <cassert>
#include <vector>

typedef long long int64;
const int mod = 1e9 + 7, N = 5e5 + 10;

int inv[N], fact[N], ifact[N];
int pw_m[N], a[N], b[N], s[N];
int p[N], pc;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int S(int n, int m) {
  if (m == 1) return (int64)n * (n - 1) / 2 % mod;
  inv[1] = fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
  for (int i = 2; i <= m + 1; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    fact[i] = (int64)i * fact[i - 1] % mod;
    ifact[i] = (int64)inv[i] * ifact[i - 1] % mod;
  }
  for (int i = 1; i <= m + 1; ++i) {
    pw_m[i] = 1;
    p[i] = 0;
  }
  for (int i = 2; i <= m + 1; ++i) {
    if (!p[i]) p[pc++] = i, pw_m[i] = pow_mod(i, m);
    for (int j = 0, u = (m + 1) / i; j < pc && p[j] <= u; ++j) {
      p[i * p[j]] = 1;
      pw_m[i * p[j]] = (int64)pw_m[i] * pw_m[p[j]] % mod;
      if (i % p[j] == 0) break;
    }
  }
  a[0] = 1, b[0] = 0;
  for (int i = 0; i <= m; ++i) {
    a[i + 1] = (int64)inv[m] * a[i] % mod;
    b[i + 1] = (int64)inv[m] * (pw_m[i] + b[i]) % mod;
  }
  int ca = 0, cb = 0;
  for (int i = 0; i <= m + 1; ++i) {
    int64 binom = (int64)fact[m + 1] * ifact[i] % mod * ifact[m + 1 - i] % mod;
    if (i & 1) binom = mod - binom;
    ca = (ca + binom * a[i]) % mod;
    cb = (cb + binom * b[i]) % mod;
  }
  int64 x = int64(mod - cb) * pow_mod(ca, mod - 2) % mod;
  if (n <= m) {
    return (pow_mod(m, n) * ((int64)a[n] * x % mod + b[n]) + mod - x) % mod;
  } else {
    int ret = 0, v = 1;
    s[m + 1] = 1;
    for (int i = m; i >= 0; --i) {
      v = (int64)v * (n - i) % mod;
      s[i] = (int64)s[i + 1] * (n - i) % mod;
    }
    v = pow_mod(v, mod - 2);
    for (int i = 0; i <= m; ++i) {
      int64 inv2 = (int64)v * s[i + 1] % mod;
      v = (int64)v * (n - i) % mod;
      int64 mul = (int64)ifact[i] * ifact[m - i] % mod * inv2 % mod;
      if ((m - i) & 1) mul = mod - mul;
      ret += ((int64)a[i] * x % mod + b[i]) * mul % mod;
      if (ret >= mod) ret -= mod;
    }
    for (int i = n - m; i <= n; ++i) {
      ret = (int64)ret * i % mod;
    }
    return (pow_mod(m, n) * ret + mod - x) % mod;
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  printf("%d\n", S(n + 1, m));
  return 0;
}

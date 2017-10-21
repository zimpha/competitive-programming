#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

typedef long long int64;
const int mod = 1e9 + 7, N = 1e6 + 10;

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

int value(char *n, int mod) {
  int r = 0;
  for (int i = 0; n[i]; ++i) {
    r = ((int64)r * 10 + n[i] - '0') % mod;
  }
  return r;
}

int S(char *n, int m) {
  int nn = value(n, mod);
  for (int i = 1; i <= m; ++i) {
    pw_m[i] = 1;
    p[i] = 0;
  }
  for (int i = 2; i <= m; ++i) {
    if (!p[i]) p[pc++] = i, pw_m[i] = pow_mod(i, m);
    for (int j = 0, u = (m) / i; j < pc && p[j] <= u; ++j) {
      p[i * p[j]] = 1;
      pw_m[i * p[j]] = (int64)pw_m[i] * pw_m[p[j]] % mod;
      if (i % p[j] == 0) break;
    }
  }
  if (strlen(n) <= 6 && nn <= m) {
    int ret = 1;
    for (int i = 2; i <= nn; ++i) {
      ret = ((int64)ret * 2 + pw_m[i] - pw_m[i - 1] + mod) % mod;
    }
    return ret;
  }
  inv[1] = fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
  for (int i = 2; i <= m; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    fact[i] = (int64)i * fact[i - 1] % mod;
    ifact[i] = (int64)inv[i] * ifact[i - 1] % mod;
  }
  a[0] = 1, b[0] = 0;
  for (int i = 1; i <= m; ++i) {
    a[i] = 2ll * a[i - 1] % mod;
    b[i] = (2ll * b[i - 1] + pw_m[i - 1] - pw_m[i] + mod) % mod;
  }
  int ca = 0, cb = 0;
  for (int i = 0; i <= m; ++i) {
    int64 binom = (int64)fact[m] * ifact[i] % mod * ifact[m - i] % mod;
    if (i & 1) binom = mod - binom;
    ca = (ca + binom * a[i]) % mod;
    cb = (cb + binom * b[i]) % mod;
  }
  int64 x = int64(mod - cb) * pow_mod(ca, mod - 2) % mod;
  int64 ret = 0, v = 1;
  s[m] = 1;
  for (int i = m - 1; i >= 0; --i) {
    v = (int64)v * (nn - i + mod) % mod;
    s[i] = (int64)s[i + 1] * (nn - i + mod) % mod;
    if (i == nn) s[i] = 1;
  }
  v = pow_mod(v, mod - 2);
  for (int i = 0; i < m; ++i) {
    int64 inv2 = (int64)v * s[i + 1] % mod;
    v = (int64)v * (nn - i + mod) % mod;
    int64 mul = (int64)ifact[i] * ifact[m - 1 - i] % mod * inv2 % mod;
    if ((m - 1 - i) & 1) mul = mod - mul;
    if (i != nn) {
      ret += ((int64)a[i] * x % mod + b[i]) * mul % mod;
    }
    if (ret >= mod) ret -= mod;
  }
  for (int i = 0; i < m; ++i) {
    ret = (int64)ret * (nn - i + mod) % mod;
  }
  if (nn <= m - 1) {
    int64 extra = (a[nn] * x % mod + b[nn]) * ifact[nn] % mod * ifact[m - 1 - nn] % mod;
    if ((m - 1 - nn) & 1) extra = mod - extra;
    for (int i = 0; i < m; ++i) {
      if (i != nn) extra = extra * (nn - i + mod) % mod;
    }
    ret = (ret + extra) % mod;
  }
  int64 g1 = (a[1] * x + b[1]) % mod;
  ret = pow_mod(2, value(n, mod - 1) - 1) * (1 + g1) % mod - ret;
  ret %= mod;
  return (ret + mod) % mod;
}

int main() {
  static char s[N];
  int m;
  scanf("%s%d", s, &m);
  printf("%d\n", S(s, m));
  return 0;
}

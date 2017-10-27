#include <cstdio>
#include <vector>

using int64 = long long;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

// f(x) is degree m - 1, given f(0), f(1), ..., f(m - 1),
// return f(n) in linear time
int64 evaluate(const std::vector<int64> &f, int64 n, int64 mod) {
  int64 m = f.size(), nn = n % mod;
  if (n < m) return f[n];
  std::vector<int64> inv(m + 1), fact(m + 1), ifact(m + 1);
  inv[1] = fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
  for (int i = 2; i <= m; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    fact[i] = (int64)i * fact[i - 1] % mod;
    ifact[i] = (int64)inv[i] * ifact[i - 1] % mod;
  }
  int64 ret = 0, v = 1;
  std::vector<int64> s(m + 1);
  s[m] = 1;
  for (int i = m - 1; i >= 0; --i) {
    v = (int64)v * (nn - i + mod) % mod;
    s[i] = (int64)s[i + 1] * (nn - i + mod) % mod;
    if (i == nn) s[i] = 1;
  }
  v = pow_mod(v, mod - 2, mod);
  for (int i = 0; i < m; ++i) {
    int64 inv2 = (int64)v * s[i + 1] % mod;
    v = (int64)v * (nn - i + mod) % mod;
    int64 mul = (int64)ifact[i] * ifact[m - 1 - i] % mod * inv2 % mod;
    if ((m - 1 - i) & 1) mul = mod - mul;
    if (i != nn) {
      ret += f[i] * mul % mod;
    }
    if (ret >= mod) ret -= mod;
  }
  for (int i = 0; i < m; ++i) {
    ret = (int64)ret * (nn - i + mod) % mod;
  }
  if (nn <= m - 1) {
    int64 extra = f[nn] * ifact[nn] % mod * ifact[m - 1 - nn] % mod;
    if ((m - 1 - nn) & 1) extra = mod - extra;
    for (int i = 0; i < m; ++i) {
      if (i != nn) extra = extra * (nn - i + mod) % mod;
    }
    ret = (ret + extra) % mod;
  }
  return ret;
}

int main() {
  const int mod = 1e9 + 7;
  int mul = 438626892;
  int rem = 221730025;
  int k = 100;
  std::vector<int64> f(k + 2);
  for (int i = 0; i <= k + 1; ++i) {
    f[i] = (i ? f[i - 1] : 0) + pow_mod(i, k, mod);
    f[i] %= mod;
  }
  int64 ret = evaluate(f, mod - 1, mod) * mul + evaluate(f, rem, mod);
  printf("%lld\n", ret % mod);
  return 0;
}

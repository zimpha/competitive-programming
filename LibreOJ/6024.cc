#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

typedef long long int64;
const int mod = 1234567891, N = 1e3 + 10;

int inv[N], fact[N], ifact[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void prepare() {
  inv[1] = fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
  for (int i = 2; i < N; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    fact[i] = (int64)i * fact[i - 1] % mod;
    ifact[i] = (int64)inv[i] * ifact[i - 1] % mod;
  }
}

// f(x) is degree m - 1, given f(0), f(1), ..., f(m - 1), return f(n)
int64 evaluate(const std::vector<int64> &f, int64 n) {
  int64 m = f.size(), nn = n % mod;
  if (n < m) return f[n];
  int64 ret = 0, v = 1;
  std::vector<int64> s(m + 1);
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
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int k, a, n, d;
    scanf("%d%d%d%d", &k, &a, &n, &d);
    std::vector<int64> g(k + 3), h(k + 4);
    // f(n) = sum_{i=0}^{n} i^k, degree k + 1
    // g(n) = sum_{i=0}^{n} f(i), degree k + 2
    // h(n) = sum_{i=0}^{n} g(a + id), degree k + 3
    int64 sum = 0;
    for (int i = 1; i <= k + 2; ++i) {
      sum = (sum + pow_mod(i, k)) % mod;
      g[i] = (g[i - 1] + sum) % mod;
    }
    for (int i = 0; i <= k + 3; ++i) {
      h[i] = ((i ? h[i - 1] : 0) + evaluate(g, a + (int64)i * d)) % mod;
    }
    printf("%lld\n", evaluate(h, n));
  }
  return 0;
}

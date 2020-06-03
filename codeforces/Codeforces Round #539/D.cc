#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  if (n == -1) return pow_mod(a, mod - 2);
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  std::vector<int64> fac(n + m, 1), ifac(n + m, 1);
  for (int i = 1; i < n + m; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  int64 ret = 0;
  for (int e = 1; e <= n - 1 && e <= m; ++e) {
    ret += pow_mod(m, n - 1 - e) * fac[m - 1] % mod * ifac[e - 1] % mod * ifac[m - e] % mod * pow_mod(n, n - e - 2) % mod * (e + 1) % mod * fac[n - 2] % mod * ifac[n - e - 1] % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

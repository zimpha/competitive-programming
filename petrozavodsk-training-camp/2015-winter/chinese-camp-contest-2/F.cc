#include <cstdio>
#include <algorithm>

using i64 = long long;

const int N = 500 + 10;
const int mod = 1e9 + 7;

i64 dp[N][N], binom[N][N], fac[N];

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  if (n > m) std::swap(n, m);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = (i64)fac[i - 1] * i % mod;
  }
  for (int i = 0; i <= m; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }

  dp[0][0] = 1;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < k; ++j) if (dp[i][j]) {
      for (int e = 0; e + i <= n; ++e) {
        i64 ways = (i64)binom[n - i][e] * binom[m - i][e] % mod * fac[e] % mod;
        ways = ways * pow_mod(j, e * (n - i) + e * (m - i) - e * e - e) % mod;
        dp[i + e][j + 1] += ways * dp[i][j];
        dp[i + e][j + 1] %= mod;
      }
    }
  }

  i64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    if (i & 1) ret += dp[i][k] * pow_mod(k, (n - i) * (m - i)) % mod;
    else ret -= dp[i][k] * pow_mod(k, (n - i) * (m - i)) % mod;
  }
  ret %= mod; ret += mod; ret %= mod;
  printf("%lld\n", ret);
  return 0;
}

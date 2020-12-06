#include <cstdio>

using i64 = long long;

const int A = 200 + 10;
const int mod = 1e9 + 7;

i64 dp[A][A];

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  dp[0][0] = 1;
  for (int i = 1; i < A; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j) dp[i][j] += dp[i - 1][j - 1] * (i - (j - 1));
      dp[i][j] %= mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, a;
    scanf("%d%d", &n, &a);
    i64 ret = 0;
    for (int l = 0; l < a; ++l) {
      i64 ways = pow_mod(a - l, n - a);
      for (int i = n - a + 1; i <= n - l; ++i) {
        ways = ways * (n - l - (i - 1)) % mod;
      }
      if (l & 1) ret -= ways * dp[a][l] % mod;
      else ret += ways * dp[a][l] % mod;
    }
    ret %= mod; ret += mod; ret %= mod;
    printf("%lld\n", ret);
  }
  return 0;
}

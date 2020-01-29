#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 998244353;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int64> pw(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * k % mod;
  }
  std::vector<int64> dp(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (i & 1) dp[i] += i * pw[(i + 1) / 2] % mod;
    else dp[i] += i / 2 * (pw[i / 2] + pw[i / 2 + 1]) % mod;
    dp[i] %= mod; dp[i] += mod; dp[i] %= mod;
    for (int j = i + i; j <= n; j += i) dp[j] -= dp[i] * (j / i) % mod;
  }
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += dp[i] * (n / i) % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

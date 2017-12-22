#include <cstdio>

constexpr int N = 300 + 10, K = N * (N - 1) / 2;
constexpr int mod = 1e9 + 7;

int dp[N][K];

int main() {
  dp[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    dp[i][0] = 1;
    for (int j = 1; j <= i * (i - 1) / 2; ++j) {
      dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;
      if (j >= i) dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + mod) % mod;
    }
  }
  int n, k;
  scanf("%d%d", &n, &k);
  int ret = 0;
  for (int i = 0; i <= k; ++i) {
    ret = (ret + dp[n][i]) % mod;
  }
  printf("%d\n", ret);
  return 0;
}

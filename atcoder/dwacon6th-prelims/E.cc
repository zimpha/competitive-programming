#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int M = 510, mod = 1e9 + 7;

int dp[M][M], binom[M][M];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m); m++;
  std::vector<int> cnt(m + 1);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x]++;
  }
  for (int i = 0; i <= m; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  dp[0][0] = mod - 1;
  for (int x = m; x >= 1; --x) {
    for (int i = m / x; i >= 0; --i) for (int j = 0; j <= m; ++j) {
      if (!dp[i][j]) continue;
      for (int k = 1; k * x + j <= m; ++k) {
        int w = (int64)dp[i][j] * binom[i + k][k] % mod;
        if (k & 1) add(dp[i + k][k * x + j], mod - w);
        else add(dp[i + k][k * x + j], w);
      }
    }
    if (cnt[x]) {
      for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) if (dp[i][j]) {
          for (int k = 0; k < cnt[x]; ++k) {
            dp[i][j] = (int64)dp[i][j] * (j - i * x + mod) % mod;
          }
        }
      }
    }
  }
  int64 ret = 0;
  for (int i = 1; i <= m; ++i) {
    ret += dp[i][m];
  }
  printf("%lld\n", ret % mod);
  return 0;
}

#include <cstdio>

const int N = 200;

int dp[N][N], p[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
      scanf("%d", p + i);
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
        dp[i][j] = -1;
      }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i) if (p[i] != -1) {
      for (int j = 1; j <= n; ++j) {
        for (int k = i; k <= m; ++k) {
          if (dp[j - 1][k - i] == -1) continue;
          if (dp[j][k] == -1 || dp[j][k] > dp[j - 1][k - i] + p[i]) {
            dp[j][k] = dp[j - 1][k - i] + p[i];
          }
        }
      }
    }
    int ret = -1;
    for (int i = 0; i <= n; ++i) if (dp[i][m] != -1) {
      if (ret == -1 || dp[i][m] < ret) ret = dp[i][m];
    }
    printf("%d\n", ret);
  }
  return 0;
}

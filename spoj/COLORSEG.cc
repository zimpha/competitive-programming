#include <cstdio>
#include <algorithm>

const int N = 51, M = 51, mod = 1000003;

int dp[M][N][M][M];
int gcd[M * 2][M * 2];

int main() {
  for (int i = 1; i <= 100; ++i) {
    for (int j = 1; j <= 100; ++j) {
      gcd[i][j] = std::__gcd(i, j);
    }
  }
  for (int m = 1; m <= 50; ++m) {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        dp[m][1][i][j] = 1;
      }
    }
    for (int s = 1; s < 50; ++s) {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          for (int k = 0; k < m; ++k) {
            if (gcd[i + j + 2][j + k + 2] == 1) {
              dp[m][s + 1][j][k] += dp[m][s][i][j];
              dp[m][s + 1][j][k] %= mod;
            }
          }
        }
      }
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 1) printf("Case %d: %d\n", cas, m);
    else {
      int ret = 0;
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          ret += dp[m][n - 1][i][j];
          ret %= mod;
        }
      }
      printf("Case %d: %d\n", cas, ret);
    }
  }
  return 0;
}

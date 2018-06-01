#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 52;

int dp[N][N][N][N];
char a[N], b[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", a + 1, b + 1);
    int n = strlen(a + 1), m = strlen(b + 1);
    int ret = 0;
    for (int d1 = 0; d1 <= n; ++d1) for (int d2 = 0; d2 <= m; ++d2) {
      for (int i = 1, j = d1; j <= n; ++i, ++j) {
        for (int k = 1, l = d2; l <= m; ++k, ++l) {
          if (d1 + d2 <= 1) dp[i][j][k][l] = 1;
          else {
            dp[i][j][k][l] = 0;
            if (d1 > 1 && a[i] == a[j]) dp[i][j][k][l] |= dp[i + 1][j - 1][k][l];
            if (d1 && d2 && a[i] == b[l]) dp[i][j][k][l] |= dp[i + 1][j][k][l - 1];
            if (d1 && d2 && b[k] == a[j]) dp[i][j][k][l] |= dp[i][j - 1][k + 1][l];
            if (d2 > 1 && b[k] == b[l]) dp[i][j][k][l] |= dp[i][j][k + 1][l - 1];
          }
          if (dp[i][j][k][l]) ret = std::max(ret, d1 + d2);
        }
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

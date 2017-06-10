#include <cstdio>
#include <cstring>

const int N = 200 + 10;

double dp[N][N];
char map[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(map, '.', sizeof(map));
    for (int i = 0; i < n; ++i) {
      if (i & 1) {
        for (int j = 0; j < m - 1; ++j) map[i][j * 2 + 1] = 'x';
        map[i][0] = map[i][m * 2 - 2] = ' ';
      } else{
        for (int j = 0; j < m; ++j) map[i][j * 2] = 'x';
      }
    }
    int k, target;
    scanf("%d%d", &target, &k);
    for (int i = 0; i < k; ++i) {
      int r, c;
      scanf("%d%d", &r, &c);
      map[r][c * 2 + r % 2] = '.';
    }
    memset(dp, 0, sizeof(dp));
    dp[n - 1][target * 2 + 1] = 1.0;
    for (int i = n - 2; i >= 0; --i) {
      for (int j = 0; j < m * 2 - 1; ++j) {
        if (map[i][j] != '.') continue;
        if (map[i + 1][j] == 'x') {
          if (map[i + 1][j - 1] == ' ') dp[i][j] = dp[i + 1][j + 1];
          else if (map[i + 1][j + 1] == ' ') dp[i][j] = dp[i + 1][j - 1];
          else dp[i][j] = (dp[i + 1][j - 1] + dp[i + 1][j + 1]) * 0.5;
        } else if (map[i + 1][j] == '.') {
          dp[i][j] = dp[i + 1][j];
        }
      }
    }
    int best = 0;
    for (int i = 0; i < m - 1; ++i) {
      if (dp[0][i * 2 + 1] > dp[0][best * 2 + 1]) {
        best = i;
      }
    }
    printf("Case #%d: %d %.6f\n", cas, best, dp[0][best * 2 + 1]);
  }
  return 0;
}

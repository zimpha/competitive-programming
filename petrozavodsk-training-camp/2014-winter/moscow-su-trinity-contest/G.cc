#include <cstdio>
#include <cstring>

const int N = 2000 + 10;
int dp[N][N], from[N][N], cnt[N];

void run() {
  char s[N], t[N];
  scanf("%s%s", t, s);
  int n = strlen(s), m = strlen(t);
  dp[0][0] = from[0][0] = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i][j] = 0;
      if (j && dp[i][j - 1] > dp[i][j]) {
        dp[i][j] = dp[i][j - 1];
        from[i][j] = 0;
      }
      if (i && j && s[i - 1] == t[j - 1] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        from[i][j] = 1;
      }
      if (i && dp[i - 1][j] > dp[i][j]) {
        dp[i][j] = dp[i - 1][j];
        from[i][j] = 2;
      }
    }
  }
  for (int i = 0; i <= n; ++i) cnt[i] = dp[i][m];
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) dp[i + 1][j] = cnt[j];
    // re-root
    int x = i + 1, y = 0;
    while (y <= m && from[x][y] == 0) ++y;
    for (; y <= m && x <= n; ++x) {
      from[x][y] = 0, --cnt[x];
      if (x == n) break;
      for (; y <= m; ++y) {
        if (from[x + 1][y] == 2) break;
        if (y + 1 <= m && from[x + 1][y + 1] == 1) {
          ++y; break;
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      printf("%d ", dp[i][j]);
    }
    puts("");
  }
}

int main() {
  run();
  return 0;
}


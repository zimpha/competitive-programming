#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

const int N = 102, M = 10001;

int dp[2][N][M];
int f[N][M], g[N][M];
int a[N];

void upd(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  int n, l, r, m;
  scanf("%d%d%d%d", &n, &l, &r, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < l; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(dp[u], -1, sizeof(dp[u]));
    if (i == 0) dp[u][l - 1][0] = 0;
    for (int j = l - 1; j <= r; ++j) {
      for (int k = 0; k <= m; ++k) {
        if (dp[v][j][k] != -1) upd(dp[u][j][k], dp[v][j][k]);
        if (j >= l && dp[u][j - 1][k] != -1) upd(dp[u][j][k], dp[u][j - 1][k] + a[j]);
        if (i >= 1 && j >= l && k >= j - i && dp[v][j - 1][k - (j - i)] != -1) upd(dp[u][j][k], dp[v][j - 1][k - (j - i)] + a[i]);
      }
    }
  }
  for (int i = l; i <= r; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = dp[(l - 1) & 1][i][j];
      if (j) upd(f[i][j], f[i][j - 1]);
    }
  }
  memset(dp, -1, sizeof(dp));
  for (int i = n + 1; i > r; --i) {
    int u = i & 1, v = u ^ 1;
    memset(dp[u], -1, sizeof(dp[u]));
    if (i == n + 1) dp[u][r + 1][0] = 0;
    for (int j = r + 1; j >= l; --j) {
      for (int k = 0; k <= m; ++k) {
        if (dp[v][j][k] != -1) upd(dp[u][j][k], dp[v][j][k]);
        if (j <= r && dp[u][j + 1][k] != -1) upd(dp[u][j][k], dp[u][j + 1][k] + a[j]);
        if (i <= n && j <= r && k >= i - j && dp[v][j + 1][k - (i - j)] != -1) upd(dp[u][j][k], dp[v][j + 1][k - (i - j)] + a[i]);
      }
    }
  }
  for (int i = r; i >= l; --i) {
    for (int j = 0; j <= m; ++j) {
      g[i][j] = dp[(r + 1) & 1][i][j];
      if (j) upd(g[i][j], g[i][j - 1]);
    }
  }
  int ret = std::min(f[r][m], g[l][m]);
  for (int i = l; i < r; ++i) {
    for (int j = 0; j <= m; ++j) {
      ret = std::min(ret, f[i][j] + g[i + 1][m - j]);
    }
  }
  printf("%d\n", ret);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 5000 + 10;

int a[N], dp[2][N][3];

inline void update(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  memset(dp, -1, sizeof(dp));
  dp[0][0][2] = dp[0][1][0] = 0;
  for (int i = 0; i < n; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(dp[v], -1, sizeof(dp[v]));
    for (int j = 0; j <= i / 2 + 1; ++j) {
      if (dp[u][j][0] != -1) update(dp[v][j][1], dp[u][j][0] + (i == n - 1 ? 0 : std::max(a[i + 1] - a[i] + 1, 0)));
      if (dp[u][j][1] != -1) {
        update(dp[v][j][2], dp[u][j][1]);
        if (i != n - 1) update(dp[v][j + 1][0], dp[u][j][1] + std::max(std::min(a[i - 1] - 1, a[i]) - a[i + 1] + 1, 0));
      }
      if (dp[u][j][2] != -1) {
        if (i != n - 1) update(dp[v][j + 1][0], dp[u][j][2] + std::max(a[i] - a[i + 1] + 1, 0));
        update(dp[v][j][2], dp[u][j][2]);
      }
    }
  }
  for (int i = 1; i <= (n + 1) / 2; ++i) {
    int ret = -1;
    for (int j = 0; j <= 2; ++j) {
      if (dp[n & 1][i][j] != -1) update(ret, dp[n & 1][i][j]);
    }
    printf("%d ", ret);
  }
  puts("");
  return 0;
}

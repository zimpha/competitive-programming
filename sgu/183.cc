#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 10000 + 10, M = 100 + 10;
const int inf = 0x3f3f3f3f;

int a[N], dp[M][M];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = std::min(dp[i][j - 1], a[i] + a[i - j]);
    }
  }
  for (int i = m; i < n; ++i) {
    memset(dp[i % m], 0x3f, sizeof(dp[i % m]));
    for (int j = 1; j < m; ++j) {
      dp[i % m][j] = std::min(dp[i % m][j - 1], dp[(i - j + m) % m][m - j] + a[i]);
    }
  }
  int ret = inf;
  for (int i = n - m + 1; i < n; ++i) {
    for (int j = 1; j < m && j <= i; ++j) {
      if (n - (i - j) <= m) ret = std::min(ret, dp[i % m][j]);
    }
  }
  printf("%d\n", ret);
  return 0;
}

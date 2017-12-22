#include <cstdio>
#include <algorithm>

using int64 = long long;
const int N = 5000 + 10;

int dp[N][N], sum[N][N];
int cut[N][N], a[N], xs[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    xs[i - 1] = a[i];
  }
  std::sort(xs, xs + n);
  int m = std::unique(xs, xs + n) - xs;
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(xs, xs + m, a[i]) - xs + 1;
    sum[i][a[i]] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  }
  for (int i = 1; i <= n; ++i) {
    dp[i][i] = 0;
    for (int j = i + 1; j <= n; ++j) {
      dp[i][j] = dp[i][j - 1] + j - i - (sum[j - 1][a[j]] - sum[i - 1][a[j]]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    cut[i][1] = 0;
    sum[i][1] = dp[1][i];
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = std::min(k, i); j > 1; --j) {
      int l = cut[i - 1][j], r = cut[i][j + 1];
      if (j + 1 > std::min(k, i)) r = i - 1;
      l = std::max(l, j - 1);
      sum[i][j] = 1e9;
      for (int k = l; k <= r; ++k) {
        int cost = sum[k][j - 1] + dp[k + 1][i];
        if (cost <= sum[i][j]) {
          sum[i][j] = cost;
          cut[i][j] = k;
        }
      }
    }
  }
  printf("%d\n", sum[n][k]);
  return 0;
}

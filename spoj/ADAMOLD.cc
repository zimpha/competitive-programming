#include <cstdio>
#include <algorithm>

using int64 = long long;
const int N = 5000 + 10;

int64 sum[N][N], dp[N][N];
int cut[N][N], a[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  ++k;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    for (int j = 1; j <= i; ++j) {
      sum[i][j] = sum[j][i] = a[i] ^ a[j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  }
  for (int i = 1; i <= n; ++i) {
    cut[i][1] = 0;
    dp[i][1] = sum[i][i] / 2;
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = std::min(k, i); j > 1; --j) {
      int l = cut[i - 1][j], r = cut[i][j + 1];
      if (j + 1 > std::min(k, i)) r = i - 1;
      l = std::max(l, j - 1);
      dp[i][j] = 1ll << 60;
      for (int k = l; k <= r; ++k) {
        int64 cost = dp[k][j - 1] + (sum[i][i] - sum[i][k] - sum[k][i] + sum[k][k]) / 2;
        if (cost <= dp[i][j]) {
          dp[i][j] = cost;
          cut[i][j] = k;
        }
      }
    }
  }
  printf("%lld\n", dp[n][k]);
  return 0;
}

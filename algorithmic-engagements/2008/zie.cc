#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 110;

int dp[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += x[i] * y[(i + 1) % n] - y[i] * x[(i + 1) % n];
  }
  if (sum < 0) {
    std::reverse(x.begin(), x.end());
    std::reverse(y.begin(), y.end());
  }
  int ret = -1e9;
  for (int it = 0; it < n / m * 2; ++it) {
    int s = rand() % n;
    for (int i = 1; i <= m; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i][j] = -1e9;
      }
    }
    dp[1][0] = 0;
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) if (dp[i][j] != -1e9) {
        for (int k = j + 1; k < n; ++k) {
          dp[i + 1][k] = std::max(dp[i + 1][k], dp[i][j] + x[(j + s) % n] * y[(k + s) % n] - y[(j + s) % n] * x[(k + s) % n]);
        }
      }
    }
    for (int i = 0; i < n; ++i) if (dp[m][i] != -1e9) {
      ret = std::max(ret, dp[m][i] + x[(i + s) % n] * y[s] - y[(i + s) % n] * x[s]);
    }
  }
  printf("%d.%d\n", ret / 2, ret % 2 * 5);
  return 0;
}

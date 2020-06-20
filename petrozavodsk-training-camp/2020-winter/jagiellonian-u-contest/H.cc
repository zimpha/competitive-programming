#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 310;

double dp[N][N][2];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d", &n);
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
    std::vector<std::vector<int>> edges(n);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        dp[i][j][0] = dp[i][j][1] = 0;
      }
    }

    memset(dp, 0, sizeof(dp));
    double ret = 0;
    for (int len = 1; len < n; ++len) {
      for (int i = 0; i < n; ++i) {
        int j = (i + len) % n;
        for (auto &k: edges[i]) {
          int t_len = k >= i ? k - i : n - i + k;
          if (t_len > len) continue;
          double dis = hypot(x[i] - x[k], y[i] - y[k]);
          dp[len][i][0] = std::max(dp[len][i][0], std::max(dp[t_len - 1][(i + 1) % n][1], dp[len - t_len][k][0]) + dis);
        }
        for (auto &k: edges[j]) {
          int t_len = k >= i ? k - i : n - i + k;
          if (t_len > len) continue;
          double dis = hypot(x[j] - x[k], y[j] - y[k]);
          dp[len][i][1] = std::max(dp[len][i][1], std::max(dp[t_len][i][1], dp[len - t_len - 1][k][0]) + dis);
        }
        ret = std::max(ret, dp[len][i][0]);
        ret = std::max(ret, dp[len][i][1]);
      }
    }
    printf("%.10f\n", ret);
  }
  return 0;
}

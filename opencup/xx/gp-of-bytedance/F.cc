#include <cstdio>
#include <vector>

const int N = 4e4 + 10;

int dp[2][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, c;
    scanf("%d%d", &n, &c);
    std::vector<int> a, b;
    int sumw = 0, maxw = 0;
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      if (x > maxw) maxw = x;
      if (sumw + x > c) b.push_back(x);
      else {
        sumw += x;
        a.push_back(x);
      }
    }
    int na = a.size(), nb = b.size(), m = maxw * 2;
    if (!na || !nb) {
      printf("%d\n", sumw);
      continue;
    }
    for (int i = 0; i <= m; ++i) dp[0][i] = dp[1][i] = N;
    int cc = c + 1 - maxw;
    dp[0][sumw - cc] = -1;
    for (int i = 0; i < nb; ++i) {
      int u = i & 1, v = (i + 1) & 1;
      for (int k = 0; k < m; ++k) dp[v][k] = dp[u][k];
      for (int k = 0; k < maxw; ++k) {
        dp[v][k + b[i]] = std::min(dp[v][k + b[i]], dp[u][k]);
      }
      for (int k = m - 1; k >= maxw; --k) {
        for (int j = dp[v][k] + 1; j < na && j <= dp[u][k]; ++j) {
          dp[v][k - a[j]] = std::min(dp[v][k - a[j]], j);
        }
      }
    }
    int ret = c;
    while (dp[nb & 1][ret - cc] == N) --ret;
    printf("%d\n", ret);
  }
  return 0;
}

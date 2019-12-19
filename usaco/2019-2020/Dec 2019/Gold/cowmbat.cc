#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

int cost[26][26];
int sum[26][N];
char s[N];

int main() {
  freopen("cowmbat.in", "r", stdin);
  freopen("cowmbat.out", "w", stdout);
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  scanf("%s", s + 1);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &cost[i][j]);
    }
  }
  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        cost[i][j] = std::min(cost[i][j], cost[i][k] + cost[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      sum[j][i] = sum[j][i - 1] + cost[s[i] - 'a'][j];
    }
  }
  std::vector<int> mx(m, 1e9);
  std::vector<int> dp(n + 1, -1);
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) if (i >= k) {
    if (dp[i - k] != -1) {
      for (int j = 0; j < m; ++j) {
        mx[j] = std::min(mx[j], dp[i - k] - sum[j][i - k]);
      }
    }
    for (int j = 0; j < m; ++j) {
      if (dp[i] == -1 || dp[i] > mx[j] + sum[j][i]) {
        dp[i] = mx[j] + sum[j][i];
      }
    }
  }
  printf("%d\n", dp[n]);
  return 0;
}

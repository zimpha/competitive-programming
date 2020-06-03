#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

const int mod = 1e9 + 7;

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) std::cin >> g[i];
  std::vector<std::vector<int>> dp(n);
  for (int i = 0; i < n; ++i) {
    dp[i].resize(m);
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '#') continue;
      if (i) dp[i][j] += dp[i - 1][j];
      if (j) dp[i][j] += dp[i][j - 1];
      if (!i && !j) dp[i][j] = 1;
      dp[i][j] %= mod;
    }
  }
  printf("%d\n", dp[n - 1][m - 1]);
  return 0;
}

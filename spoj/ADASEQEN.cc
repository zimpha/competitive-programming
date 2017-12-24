#include <cstdio>
#include <algorithm>

const int N = 2000 + 10;

int dp[N][N], cost[26];
char s[N], t[N];
int n, m;

int main() {
  scanf("%d%d", &n, &m); 
  for (int i = 0; i < 26; ++i) {
    scanf("%d", &cost[i]);
  }
  scanf("%s%s", s, t);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j]);
      dp[i][j + 1] = std::max(dp[i][j + 1], dp[i][j]);
      if (s[i] == t[j]) {
        dp[i + 1][j + 1] = std::max(dp[i + 1][j + 1], dp[i][j] + cost[s[i] - 'a']);
        ret = std::max(ret, dp[i + 1][j + 1]);
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

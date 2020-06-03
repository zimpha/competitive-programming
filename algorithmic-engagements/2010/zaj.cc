#include <cstdio>
#include <string>
#include <algorithm>

const int N = 1000 + 10;
char s[N];
int dp[N][N], n;

int lcs(const std::string &s, const std::string &t) {
  for (size_t i = 1; i <= s.size(); ++ i) {
    for (size_t j = 1; j <= t.size(); ++ j) {
      if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
    }
  }
  return dp[s.size()][t.size()];
}

int main() {
  scanf("%d%s", &n, s);
  int ret = 0;
  for (int i = 1; i < n; ++ i) {
    ret = std::max(ret, lcs(std::string(s, s + i), std::string(s + i, s + n)));
  }
  printf("%d\n", n - ret * 2);
  return 0;
}

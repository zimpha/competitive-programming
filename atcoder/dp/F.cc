#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 3000 + 10;

char s[N], t[N];
int dp[N][N], from[N][N];

int main() {
  scanf("%s%s", s, t);
  int n = strlen(s);
  int m = strlen(t);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        from[i][j] = 0;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        if (dp[i][j] == dp[i - 1][j]) from[i][j] = 1;
        else from[i][j] = 2;
      }
    }
  }
  int x = n, y = m;
  std::vector<char> ret;
  while (x && y) {
    if (from[x][y] == 0) {
      ret.push_back(s[x - 1]);
      --x, --y;
    } else if (from[x][y] == 1) {
      --x;
    } else {
      --y;
    }
  }
  std::reverse(ret.begin(), ret.end());
  for (auto &&c: ret) putchar(c);
  puts("");
  return 0;
}

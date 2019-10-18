#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

const int N = 200;
int dp[N][N];
char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
      dp[i][i] = 1;
      dp[i][i - 1] = 0;
    }
    for (int l = 2; l <= n; ++l) {
      for (int i = 1; i + l - 1 <= n; ++i) {
        int j = i + l - 1;
        if (s[i - 1] == s[j - 1]) dp[i][j] = dp[i + 1][j - 1] + 2;
        else dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]) + 2;
      }
    }
    std::string ret;
    int l = 1, r = n;
    int x = 0;
    while (l < r) {
      int nl, nr;
      std::string now = "";
      if (s[l - 1] == s[r - 1] && dp[l][r] == dp[l + 1][r - 1] + 2) {
        ret.push_back(s[l - 1]);
        if (now == "" || ret < now) now = ret, nl = l + 1, nr = r - 1;
        ret.pop_back();
      }
      if (dp[l][r] == dp[l + 1][r] + 2) {
        ret.push_back(s[l - 1]);
        if (now == "" || ret < now) now = ret, nl = l + 1, nr = r;
        ret.pop_back();
      }
      if (dp[l][r] == dp[l][r - 1] + 2) {
        ret.push_back(s[r - 1]);
        if (now == "" || ret < now) now = ret, nl = l, nr = r - 1;
        ret.pop_back();
      }
      ret = now;
      l = nl;
      r = nr;
    }
    if (l == r) ret.push_back(s[l - 1]);
    for (int i = dp[1][n] / 2 - 1; i >= 0; --i) ret.push_back(ret[i]);
    printf("Case %d: %d %s\n", cas, dp[1][n] - n, ret.c_str());
  }
  return 0;
}

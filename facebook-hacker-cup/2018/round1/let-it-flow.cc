#include <cstdio>
#include <cstring>

const int N = 1000 + 10, mod = 1e9 + 7;

char s[3][N];
int dp[N][3];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i) scanf("%s", s[i]);
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (s[j][i] == '#') continue;
        if (dp[i][j] == 0) continue;
        dp[i][j] %= mod;
        if (j && s[j - 1][i] != '#') dp[i + 1][j - 1] += dp[i][j];
        if (j < 2 && s[j + 1][i] != '#') dp[i + 1][j + 1] += dp[i][j];
      }
    }
    printf("Case #%d: %d\n", cas, dp[n][2] % mod);
  }
  return 0;
}

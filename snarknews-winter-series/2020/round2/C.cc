#include <cstdio>
#include <cstring>

const int N = 1e3 + 10;
const int mod = 998244353;

int dp[N][N];
int ways[N][N];
char s[N];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  scanf("%s", s);
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  ways[0][0] = 1;
  int n = strlen(s);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) if (dp[i][j] != -1) {
      if (dp[i + 1][j] == -1 || dp[i + 1][j] >= dp[i][j] + 1) {
        if (dp[i + 1][j] == -1 || dp[i + 1][j] > dp[i][j] + 1) ways[i + 1][j] = ways[i][j], dp[i + 1][j] = dp[i][j] + 1;
        else add(ways[i + 1][j], ways[i][j]);
      }
      if (s[i] == 'w' && j) {
        if (dp[i + 1][j - 1] == -1 || dp[i + 1][j - 1] >= dp[i][j]) {
          if (dp[i + 1][j - 1] == -1 || dp[i + 1][j - 1] > dp[i][j]) ways[i + 1][j - 1] = ways[i][j], dp[i + 1][j - 1] = dp[i][j];
          else add(ways[i + 1][j - 1], ways[i][j]);
        }
      }
      if (s[i] == 'm') {
        if (dp[i + 1][j + 1] == -1 || dp[i + 1][j + 1] >= dp[i][j]) {
          if (dp[i + 1][j + 1] == -1 || dp[i + 1][j + 1] > dp[i][j]) ways[i + 1][j + 1] = ways[i][j], dp[i + 1][j + 1] = dp[i][j];
          else add(ways[i + 1][j + 1], ways[i][j]);
        }
      }
    }
  }
  printf("%d\n", ways[n][0]);
  return 0;
}

#include <cstdio>
#include <cstring>

const int N = 30, mod = 1e9 + 7;

int dp[N][N][N * N];
char t[N], s[N];
int n, m;

void update(int &x, int y) {
  x = (x + y) % mod;
}

int solve(int p) {
  for (int i = 0; i < n; ++i) t[i] = '?';
  for (int i = 0; s[i]; ++i) t[i + p] = s[i];
  int small = 0, large = 0;
  for (int i = 0; s[i]; ++i) {
    small += s[i] < s[0];
    large += s[i] > s[0];
  }
  int u = s[0] - 'a' - small;
  int v = 'z' - s[0] - large;
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= u; ++j) {
      for (int k = 0; k <= m; ++k) {
        if (!dp[i][j][k]) continue;
        if (t[i] == '?') {
          if (j < u && k + n - i <= m) {
            update(dp[i + 1][j + 1][k + n - i], 1ll * dp[i][j][k] * (u - j) % mod);
          }
        }
      }
    }
  }
  return dp[n][u][m];
}

int main() {
  scanf("%d%d%s", &n, &m, s);
  int l = strlen(s);
  int ret = 0;
  for (int i = 0; i + l <= n; ++i) {
    ret = (ret + solve(i)) % mod;
  }
  return 0;
}

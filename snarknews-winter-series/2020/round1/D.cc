#include <cstdio>
#include <cstring>

int dp[2][10][1 << 19];
int n, m, p;

void upd(int &x, int y) {
  if ((x += y) >= p) x -= p;
}

int main() {
  scanf("%d%d%d", &n, &m, &p);
  int ret = 1;
  for (int i = 1; i <= n; ++i) ret = 1ll * ret * m % p;
  if (n - 1 > m * 2 - 1) {
    printf("%d\n", ret);
    return 0;
  }
  memset(dp, 0, sizeof(dp));
  int s = 1 << (m * 2 - 1), bd = -m + 1;
  for (int i = 0; i < m; ++i) dp[1][i][0] = 1;
  for (int i = 1; i < n; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(dp[v], 0, sizeof(dp[v]));
    for (int j = 0; j < m; ++j) {
      for (int mask = 0; mask < s; ++mask) {
        int w = dp[u][j][mask];
        if (w == 0) continue;
        for (int x = 0; x < m; ++x) {
          int d = x - j - bd;
          if (~mask >> d & 1) {
            upd(dp[v][x][mask ^ (1 << d)], w);
          }
        }
      }
    }
  }
  for (int x = 0; x < m; ++x) {
    for (int mask = 0; mask < s; ++mask) {
      upd(ret, p - dp[n & 1][x][mask]);
    }
  }
  printf("%d\n", ret);
  return 0;
}

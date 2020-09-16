#include <cstdio>
#include <cstring>
#include <vector>

using i64 = long long;

const int N = 1e6 + 10;

i64 dp[2][N][2];

int main() {
  freopen("puzzle.in", "r", stdin);
  freopen("puzzle.out", "w", stdout);
  int n, a, b, c, p, t, m = 0;
  scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &p, &t);
  std::vector<int> x(p + 1);
  x[0] = a;
  for (m = 1; ; ++m) {
    x[m] = (1ll * x[m - 1] * b + c) % p;
    if (x[m] == x[0]) break;
  }
  for (int i = 0; i < n; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(dp[v], 0, sizeof(dp[v]));
    for (int j = 0; j < m; ++j) {
      int w = x[j] >= t;
      int ls = (2 * j + 1) % m;
      int rs = (2 * j + 2) % m;
      if (w == 0) {
        dp[v][j][0] = dp[u][ls][0] + dp[u][rs][0];
        dp[v][j][1] = dp[u][ls][1] + dp[u][rs][1] + 1;
      } else {
        dp[v][j][0] = dp[u][ls][0] + dp[u][rs][1] + 1;
        dp[v][j][1] = dp[u][ls][0] + dp[u][rs][1];
      }
    }
  }
  printf("%lld\n", dp[n & 1][0][0]);
  return 0;
}

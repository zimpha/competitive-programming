#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 201;

// f_{i,j,k}: i nodes, last subtree size j, height <= k (single vertex is height 1)
int64 f[N][N][N], inv[N];
// g_{i j}: i nodes, height j (single vertex is height 0)
int64 g[N][N], dp[N];

int main() {
  int n, d, p;
  scanf("%d%d%d", &n, &d, &p);
  if (n == 1 || d == 2 || (n == 2 && d == 1)) {
    puts("1");
    return 0;
  }
  if (d < 2) {
    puts("0");
    return 0;
  }
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = int64(p - p / i) * inv[p % i] % p;
  }
  int h = d / 2;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (int k = 0; k <= h && k <= i; ++k) {
        if (i == 0) f[i][j][k] = 1;
        else if (j < 1 || k < 1) f[i][j][k] = 0;
        else {
          int64 w = f[j - 1][j - 1][std::min(j - 1, k - 1)], r = 1;
          for (int t = 0; t <= i / j; ++t) {
            int x = i - j * t;
            int y = std::min(x, j - 1);
            int z = std::min(x, k);
            f[i][j][k] += r * f[x][y][z] % p;
            r = r * (w + t) % p * inv[t + 1] % p;
          }
          f[i][j][k] %= p;
        }
      }
    }
  }
  g[1][0] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      g[i][j] = (f[i - 1][i - 1][j] - f[i - 1][i - 1][j - 1] + p) % p;
    }
  }
  int64 ret = 0;
  if (d & 1) {
    for (int i = 1; i < n; ++i) {
      ret += g[i][h] * g[n - i][h] % p;
    }
    if (n % 2 == 0) {
      ret -= g[n / 2][h] * g[n / 2][h] % p;
      ret += g[n / 2][h] * (g[n / 2][h] + 1) % p;
    }
    ret = ret % p * inv[2] % p;
  } else {
    for (int i = h + 1; i <= n; ++i) {
      dp[i] = g[i][h];
      for (int j = 1; j < i; ++j) {
        dp[i] -= f[j][j][std::min(j, h - 1)] * dp[i - j] % p;
      }
      dp[i] = (dp[i] % p + p) % p;
    }
    for (int i = h + 1; i <= n; ++i) {
      dp[i] = (dp[i] + p - g[i - 1][h - 1]) % p;
    }
    for (int i = 0; i <= n; ++i) {
      ret += dp[n - i] * f[i][i][std::min(h - 1, i)] % p;
    }
    ret %= p;
  }
  printf("%lld\n", ret);
  return 0;
}

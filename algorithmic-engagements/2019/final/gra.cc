#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 500 + 10;

int64 binom[N][N], fac[N * 2], pw[N * 2];
// number of perfect match of 1, 2, ..., x} and 1, 2, ..., y, x + 1, ..., 2x - y}
// no i - i matches
int64 match[N][N];
// first i, choose j forbidden
int64 ways[N][N * 2];
int64 dp[N][N];
int n, mod;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void solve() {
  const int64 i2 = pow_mod(2, mod - 2);
  fac[0] = pw[0] = 1;
  for (int i = 1; i <= n * 2; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    pw[i] = pw[i - 1] * i2 % mod;
  }
  for (int i = 0; i <= n; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  // match[x][y] = \sum_{i=0}^{y} (x-i)! * (-1)^i * \binom{y}{i}
  //             = match[x][y - 1] - match[x - 1][y - 1];
  for (int x = 0; x <= n; ++x) {
    match[x][0] = fac[x];
    for (int y = 1; y <= x; ++y) {
      match[x][y] = (match[x][y - 1] + mod - match[x - 1][y - 1]) % mod;
    }
  }
  ways[0][0] = 1;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= i * 2; ++j) {
      ways[i][j] %= mod;
      ways[i + 1][j] += ways[i][j];
      ways[i + 1][j + 1] += ways[i][j] * 4;
      ways[i + 1][j + 2] += ways[i][j] * 2;
    }
  }

  // could be optimize to O(n^2)
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; x + y <= n; ++y) {
      dp[x][y] = fac[2 * (x + y)];
      for (int i = 1; i <= y * 2; ++i) {
        if (i & 1) dp[x][y] -= fac[2 * (x + y) - i] * ways[y][i] % mod;
        else dp[x][y] += fac[2 * (x + y) - i] * ways[y][i] % mod;
      }
      dp[x][y] %= mod; dp[x][y] += mod; dp[x][y] %= mod;
      dp[x][y] = dp[x][y] * pw[x + y] % mod;
    }
  }
  int64 ret = 0;
  for (int x = 0; x <= n; ++x) for (int y = 0; y <= x; ++y) {
    if (n - x < x - y) continue;
    int64 now = binom[n][x] * binom[x][y] % mod * binom[n - x][x - y] % mod;
    now = now * match[x][y] % mod * dp[x - y][n - (2 * x - y)] % mod;
    if (x & 1) ret -= now;
    else ret += now;
  }
  ret %= mod; ret += mod; ret %= mod;
  ret = ret * pw[n] % mod;
  printf("%lld\n", ret);
}

int main() {
  scanf("%d%d", &n, &mod);
  solve();
  return 0;
}

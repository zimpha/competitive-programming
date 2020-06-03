#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e3 + 10, M = 50;
const int mod = 1e9 + 7;

int64 binom[N][N];
int64 ways[M][M][N];
int64 dp[N][M];
int64 pw[N];

int64 count(int x, int y, int n) {
  int dx = x + y, dy = x - y;
  if (n % 2 != std::abs(dx) % 2) return 0;
  int a = (n + dx) / 2, b = (n + dy) / 2;
  if (a < 0 || a > n || b < 0 || b > n) return 0;
  return binom[n][a] * binom[n][b] % mod;
}

int main() {
  int x, y, n, d;
  scanf("%d%d%d%d", &x, &y, &n, &d);
  for (int i = 0; i <= n; ++i) {
    if (i) pw[i] = pw[i - 1] * 4 % mod;
    else pw[i] = 1;
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  std::vector<std::pair<int, int>> forbid;
  for (int dx = -d; dx <= d; ++dx) {
    for (int dy = -d; dy <= d; ++dy) {
      if (std::abs(dx) + std::abs(dy) == d) {
        forbid.emplace_back(x + dx, y + dy);
      }
    }
  }
  int m = forbid.size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int k = 1; k <= n; ++k) {
        ways[i][j][k] = count(forbid[j].first - forbid[i].first, forbid[j].second - forbid[i].second, k);
      }
    }
  }
  int64 ret = pw[n];
  for (int a = 1; a <= n; ++a) {
    for (int i = 0; i < m; ++i) {
      dp[a][i] = count(forbid[i].first, forbid[i].second, a);
      for (int b = 1; b < a; ++b) {
        for (int j = 0; j < m; ++j) {
          dp[a][i] -= dp[b][j] * ways[j][i][a - b] % mod;
        }
      }
      dp[a][i] %= mod; dp[a][i] += mod; dp[a][i] %= mod;
      ret -= dp[a][i] * pw[n - a] % mod;
    }
  }
  ret %= mod; ret += mod; ret %= mod;
  printf("%lld\n", ret);
  return 0;
}

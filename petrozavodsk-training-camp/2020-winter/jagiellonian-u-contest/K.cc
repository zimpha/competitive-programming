#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using int64 = long long;

const int N = 144 + 10;
const int mod = 1e9 + 7;

char s[N][N], grid[N][N];
int dp[2][N][1 << 13];
int binom[N][N];

void upd(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) scanf("%s", s[i]);
    if (n < m) {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          grid[i][j] = s[j][i];
        }
      }
      std::swap(n, m);
    } else {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          grid[i][j] = s[i][j];
        }
      }
    }
    int empty = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        empty += grid[i][j] == '.';
      }
    }
    if (k * 2 > empty) {
      puts("0");
      continue;
    }
    for (int i = 0; i <= n * m; ++i) {
      binom[i][0] = binom[i][i] = 1;
      for (int j = 1; j < i; ++j) {
        binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
      }
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    int now = 0, next = 1, ms = 1 << (m + 1);
    for (int i = 0; i < n * m; ++i) {
      for (int j = 0; j <= k; ++j) for (int mask = 0; mask < ms; ++mask) dp[next][j][mask] = 0;
      int x = i / m, y = i % m;
      for (int j = 0; j <= k; ++j) for (int mask = 0; mask < ms; ++mask) {
        if (!dp[now][j][mask]) continue;
        int new_mask = (mask & (ms / 2 - 1)) >> 1;
        if (grid[x][y] == 'X') {
          if ((~mask & 1) && (~mask >> m & 1)) {
            upd(dp[next][j][new_mask], dp[now][j][mask]);
          }
        } else {
          // do not put in (x, y)
          if ((~mask & 1) && (~mask >> m & 1)) {
            upd(dp[next][j][new_mask], dp[now][j][mask]);
          }
          // (x, y) with (x, y + 1)
          if (y != m - 1 && (~mask & 1) && (~mask >> m & 1)) {
            upd(dp[next][j][new_mask | (1 << m)], dp[now][j][mask]);
          }
          // (x, y) with (x, y - 1)
          if ((mask & 1) && (~mask >> m & 1)) {
            upd(dp[next][j + 1][new_mask], dp[now][j][mask]);
          }
          // (x, y) with (x - 1, y)
          if ((~mask & 1) && (mask >> m & 1)) {
            upd(dp[next][j + 1][new_mask], dp[now][j][mask]);
          }
          // (x, y) with (x + 1, y)
          if ((~mask & 1) && (~mask >> m & 1)) {
            upd(dp[next][j][new_mask | (1 << (m - 1))], dp[now][j][mask]);
          }
        }
      }
      std::swap(now, next);
    }
    int64 ret = 0, fac = 1;
    for (int i = 0; i <= k; ++i) {
      int64 ways = (int64)binom[k][i] * dp[now][i][0] % mod * fac % mod;
      for (int j = 0; j <= k - i - 1; ++j) {
        ways = ways * binom[empty - 2 * i - 2 * j][2] % mod;
      }
      if (i & 1) ret += mod - ways;
      else ret += ways;
      fac = fac * (i + 1) % mod;
    }
    for (int i = 0; i < k; ++i) ret = ret * 2 % mod;
    printf("%lld\n", ret % mod);
  }
  return 0;
}

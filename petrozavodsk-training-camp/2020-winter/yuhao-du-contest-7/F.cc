#include <cstdio>
#include <cstring>

using int64 = long long;

const int N = 40;
const int mod = 1e9 + 7;
const int i2 = 5e8 + 4;

bool g[N][N];
int dp[1 << 18][N];
int path[1 << 18], cycle[1 << 18];
int ways[1 << 18], pw[N];
int n, m, c;

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  scanf("%d%d%d", &n, &m, &c);
  if (n & 1) ++n;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u][v] = g[v][u] = 1;
  }
  int nn = n / 2;
  pw[0] = 1;
  for (int i = 1; i <= nn; ++i) {
    pw[i] = (int64)pw[i - 1] * c % mod;
  }
  for (int s = 0; s < nn; ++s) {
    dp[1 << s][s * 2 + 1] = 1;
    int ss = 1 << (nn - s - 1);
    for (int msk = 0; msk < ss; ++msk) {
      int mask = msk << (s + 1) | (1 << s);
      for (int i = s * 2; i < n; ++i) if (dp[mask][i]) {
        for (int j = s * 2; j < n; ++j) if (~mask >> (j / 2) & 1) {
          if (!g[i][j]) continue;
          add(dp[mask | (1 << (j / 2))][j ^ 1], dp[mask][i]);
        }
      }
    }
    for (int msk = 0; msk < ss; ++msk) {
      int mask = msk << (s + 1) | (1 << s);
      for (int i = 0; i < n; ++i) {
        if (g[i][s * 2] && dp[mask][i]) {
          add(cycle[mask], dp[mask][i]);
        }
      }
    }
  }
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < nn; ++i) {
    dp[1 << i][i * 2] = 1;
    dp[1 << i][i * 2 + 1] = 1;
  }
  for (int mask = 0; mask < (1 << nn); ++mask) {
    for (int i = 0; i < n; ++i) if (dp[mask][i]) {
      for (int j = 0; j < n; ++j) if (g[i][j] && (~mask >> (j / 2) & 1)) {
        add(dp[mask | (1 << (j / 2))][j ^ 1], dp[mask][i]);
      }
    }
  }
  for (int mask = 0; mask < (1 << nn); ++mask) {
    for (int i = 0; i < n; ++i) add(path[mask], (int64)dp[mask][i] * i2 % mod);
  }
  for (int mask = 0; mask < (1 << nn); ++mask) {
    int cnt = __builtin_popcount(mask);
    cycle[mask] = (int64)cycle[mask] * pw[cnt] % mod;
    path[mask] = (int64)path[mask] * pw[cnt - 1] % mod;
  }
  ways[0] = 1;
  for (int mask = 0; mask < (1 << nn); ++mask) {
    int rest = ((1 << nn) - 1) ^ mask;
    int p = __builtin_ctz(rest);
    if (!rest) continue;
    int mm = rest >> (p + 1);
    for (int msk = mm; ; msk = (msk - 1) & mm) {
      int sub = msk << (p + 1) | (1 << p);
      add(ways[mask ^ sub], (int64)ways[mask] * (cycle[sub] + path[sub]) % mod);
      if (msk == 0) break;
    }
  }
  printf("%d\n", ways[(1 << nn) - 1]);
  return 0;
}

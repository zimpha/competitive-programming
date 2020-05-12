#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int MS = 1 << 20, ML = 1 << 10;

int cost[2], mark[400];
int n, m, d;

void upd(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

namespace small {
int dp[2][MS + 10];
int run() {
  int u = 0, v = 1, md = 1 << d;
  memset(dp[u], -1, sizeof(*dp[u]) * md);
  dp[u][0] = 0;
  for (int i = 0; i < m; ++i) {
    memset(dp[v], -1, sizeof(*dp[v]) * md);
    for (int mask = 0; mask < md; ++mask) if (dp[u][mask] != -1) {
      int new_mask = (mask >> 1) | (1 << (d - 1));
      upd(dp[v][new_mask], dp[u][mask] + cost[mask >> (d - 1)]);
      if (i < d || !mark[i - d] || (mask & 1)) upd(dp[v][mask >> 1], dp[u][mask]);
    }
    u ^= 1, v ^= 1;
  }
  int ret = -1;
  for (int mask = 0; mask < md; ++mask) if (dp[u][mask] != -1) {
    upd(ret, dp[u][mask]);
  }
  return ret;
}
}

namespace large {
int dp[2][ML + 10];
int run() {
  int w = m / d + 1, mw = 1 << w;
  int ret = -1;
  for (int mask0 = 0; mask0 < mw; ++mask0) {
    bool valid = true;
    for (int i = 0; i < w && valid; ++i) if (mark[i * d]) {
      if ((~mask0 >> i & 1) && (~mask0 >> (i + 1) & 1)) valid = false;
    }
    if (!valid) continue;
    int u = 0, v = 1;
    memset(dp[u], -1, sizeof(*dp[u]) * mw);
    dp[u][mask0] = (mask0 & 1) ? cost[0] : 0;
    for (int i = 1; i < d; ++i) {
      for (int j = i, k = 0; j < m; j += d, ++k) {
        memset(dp[v], -1, sizeof(*dp[v]) * mw);
        for (int mask = 0; mask < mw; ++mask) if (dp[u][mask] != -1) {
          int new_mask = mask | (1 << k);
          upd(dp[v][new_mask], dp[u][mask] + cost[mask >> k & 1]);
          if (j < d || !mark[j - d] || (mask >> (k - 1) & 1)) {
            upd(dp[v][mask & ((mw - 1) ^ (1 << k))], dp[u][mask]);
          }
        }
        u ^= 1, v ^= 1;
      }
    }
    for (int mask = 0; mask < mw; ++mask) if (dp[u][mask] != -1) {
      int sum = dp[u][mask];
      for (int i = d, k = 1; i < m; i += d, ++k) {
        if (mask0 >> k & 1) sum += cost[mask >> (k - 1) & 1];
      }
      upd(ret, sum);
    }
  }
  return ret;
}
}

int main() {
  scanf("%d%d%d%d", &n, &d, &cost[0], &cost[1]);
  cost[1] = std::min(cost[0], cost[1]);
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
  std::sort(x.begin(), x.end());
  d <<= 1;
  m = x.back() - x[0] + d + 1;
  for (int i = n - 1; i >= 0; --i) mark[x[i] - x[0]] = 1;
  int ret = d <= 20 ? small::run() : large::run();
  printf("%d\n", ret);
  return 0;
}

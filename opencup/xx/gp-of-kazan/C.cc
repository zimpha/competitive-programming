#include <cstdio>
#include <vector>
#include <cstring>
#include <map>

using int64 = long long;

const int N = 13, M = 1 << 13;
const int mod = 998244353;
const int i2 = 499122177;

int ways[N][M], cycle[M];
int f[N][M];
std::map<int, int> dp[M];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> edges(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u] |= 1 << v;
    edges[v] |= 1 << u;
  }

  // cycle[S] number of cycles in S
  for (int s = 0; s < n; ++s) {
    memset(f, 0, sizeof(f));
    f[s][1 << s] = 1;
    for (int mask = 0; mask < (1 << n); ++mask) {
      for (int u = s; u < n; ++u) if (mask >> u & 1) {
        for (int v = s; v < n; ++v) if ((~mask & edges[u]) >> v & 1) {
          add(f[v][mask ^ (1 << v)], f[u][mask]);
        }
      }
    }
    for (int u = 0; u < n; ++u) if (edges[s] >> u & 1) {
      for (int mask = 0; mask < (1 << n); ++mask) if (f[u][mask]) {
        add(cycle[mask], f[u][mask]);
      }
    }
  }
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (__builtin_popcount(mask) > 2) cycle[mask] = (int64)cycle[mask] * i2 % mod;
  }
  // ways[i][S] number of ways such that all cycle has common i, union is S
  for (int i = 0; i < n; ++i) {
    ways[i][0] = 1;
    for (int mask = 1; mask < (1 << n); ++mask) if (~mask >> i & 1) {
      for (int sub = mask; sub * 2 > mask; sub = (sub - 1) & mask) {
        add(ways[i][mask], (int64)cycle[sub ^ (1 << i)] * ways[i][mask ^ sub] % mod);
      }
    }
  }

  // dp[S][T] number of ways such that all leaves are S-T
  dp[1][0] = 1;
  for (int mask = 0; mask < (1 << n); ++mask) {
    int rest = ((1 << n) - 1) ^ mask;
    for (auto it = dp[mask].begin(); it != dp[mask].end(); ++it) {
      if (it->first == mask) continue;
      int p = __builtin_ctz(mask ^ it->first);
      for (int sub = rest; ; sub = (sub - 1) & rest) {
        add(dp[mask ^ sub][it->first ^ (1 << p)], (int64)it->second * ways[p][sub] % mod);
        if (!sub) break;
      }
    }
  }
  printf("%d\n", dp[(1 << n) - 1][(1 << n) - 1]);
  return 0;
}

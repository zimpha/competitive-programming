#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> succ(n), pred(n);
    for (int i = 0, u, v; i < m; ++i) {
      scanf("%d%d", &u, &v);
      --u, --v;
      succ[u] |= 1 << v;
      pred[v] |= 1 << u;
    }
    std::vector<int64> f(1 << n), g(1 << n);
    f[0] = g[0] = 1;
    for (int mask = 0; mask < (1 << n); ++mask) {
      for (int v = 0; v < n; ++v) if (~mask >> v & 1) {
        if ((pred[v] & mask) == pred[v]) {
          f[mask | (1 << v)] += f[mask];
        }
        if ((succ[v] & mask) == succ[v]) {
          g[mask | (1 << v)] += g[mask];
        }
      }
    }
    std::vector<std::vector<int64>> ret(n, std::vector<int64>(n));
    for (int mask = 0; mask < (1 << n); ++mask) {
      for (int v = 0; v < n; ++v) if (~mask >> v & 1) {
        int new_mask = ((1 << n) - 1) ^ mask ^ (1 << v);
        int64 cost = f[mask] * g[new_mask];
        for (int u = 0; u < n; ++u) if (mask >> u & 1) {
          ret[v][u] += cost;
        }
      }
    }
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        printf("%lld ", ret[u][v]);
      }
      puts("");
    }
  }
  return 0;
}

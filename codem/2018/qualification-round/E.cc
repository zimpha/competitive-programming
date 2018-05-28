#include <cstdio>
#include <vector>
#include <algorithm>

struct edge_t {
  int u, v, c, ts, td;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<edge_t> edges(m);
  for (int i = 0; i < m; ++i) {
    int u, v, c, ts_h, ts_m, td_h, td_m;
    scanf("%d%d%d%d:%d%d:%d", &u, &v, &c, &ts_h, &ts_m, &td_h, &td_m);
    --u, --v;
    edges[i] = {u, v, c, ts_h * 2 + ts_m / 30, td_h * 2 + td_m / 30};
  }
  std::vector<int> latest(n, -1);
  std::sort(edges.begin(), edges.end(), [&](const edge_t& a, const edge_t& b) {
      return a.td > b.td;
  });
  latest[n - 1] = 100;
  for (auto &&e: edges) if (latest[e.v] > e.td) {
    latest[e.u] = std::max(latest[e.u], e.ts);
  }
  std::sort(edges.begin(), edges.end(), [&](const edge_t& a, const edge_t& b) {
      return a.ts < b.ts;
  });
  std::vector<std::vector<int>> cost(n, std::vector<int>(50, -1));
  for (int i = 0; i <= 48; ++i) cost[0][i] = 0;
  for (auto &&e: edges) if (latest[e.u] > e.ts) {
    for (int i = 0; i < e.ts + (e.u == 0); ++i) if (cost[e.u][i] != -1) {
      if (cost[e.v][e.td] == -1 || cost[e.v][e.td] > cost[e.u][i] + e.c) {
        cost[e.v][e.td] = cost[e.u][i] + e.c;
      }
    }
  }
  int ret = -1;
  for (int i = 0; i <= 48; ++i) {
    if (cost[n - 1][i] != -1 && (ret == -1 || ret > cost[n - 1][i])) {
      ret = cost[n - 1][i];
    }
  }
  printf("%d\n", ret);
  return 0;
}

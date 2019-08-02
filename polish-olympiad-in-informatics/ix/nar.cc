#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> edges;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0, m; i < n - 1; ++i) {
    scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int x;
      scanf("%d", &x);
      graph[i].push_back(edges.size());
      edges.emplace_back(i, x - 1);
    }
  }
  std::vector<int> dp(edges.size(), 1), prev(n), mark(n + 1);

  std::function<void(int)> dfs = [&](int u) {
    mark[u] = 1;
    for (auto &e: graph[u]) {
      int v = edges[e].second;
      if (!mark[v]) {
        prev[v] = e;
        dfs(v);
      } else {
        int mx = 0, x = v;
        for (; mark[x] != 1; x = edges[prev[x]].first) {
          mx = std::max(mx, dp[prev[x]]);
        }
        prev[v] = e;
        for (int y = v; y != x; y = edges[prev[y]].first) {
          dp[prev[y]] = std::max(dp[prev[y]], mx + 1);
        }
      }
    }
    mark[u] = 2;
  };

  dfs(0);

  printf("%d\n", *std::max_element(dp.begin(), dp.end()));
  return 0;
}

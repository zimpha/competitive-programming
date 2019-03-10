#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, k, m;
  scanf("%d%d%d", &n, &k, &m);
  std::vector<int> dis(n, -1);
  for (int i = 0; i < k; ++i) {
    int x;
    scanf("%d", &x);
    dis[x - 1] = 0;
  }
  std::vector<std::vector<std::pair<int, int>>> edges(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }
  std::vector<bool> mark(n);
  while (true) {
    int u = -1;
    for (int i = 0; i < n; ++i) if (dis[i] != -1) {
      if (!mark[i] && (u == -1 || dis[u] > dis[i])) u = i;
    }
    if (u == -1) break;
    mark[u] = 1;
    for (auto &&e: edges[u]) {
      int v = e.first, w = e.second;
      if (mark[v]) continue;
      if (dis[v] == -1 || dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
      }
    }
  }
  printf("%d\n", *std::max_element(dis.begin(), dis.end()));
  return 0;
}

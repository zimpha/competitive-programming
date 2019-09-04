#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<std::pair<int, int>>> edges(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    edges[a].emplace_back(b, c);
    edges[b].emplace_back(a, c);
  }
  std::priority_queue<std::pair<int, int>> pq;
  std::vector<int> dis(n * 2, -1);
  pq.emplace(0, 0);
  dis[0] = 0;
  while (!pq.empty()) {
    int u = pq.top().second;
    int d = -pq.top().first;
    pq.pop();
    if (d > dis[u]) continue;
    for (auto &e: edges[u / 2]) {
      int w = d + e.second;
      int v = e.first * 2 + w % 2;
      if (dis[v] == -1 || dis[v] > w) {
        dis[v] = w;
        pq.emplace(-dis[v], v);
      }
    }
  }
  if (dis[(n - 1) * 2 + 1] == -1) puts("0");
  else printf("%d\n", dis[(n - 1) * 2 + 1]);
  return 0;
}

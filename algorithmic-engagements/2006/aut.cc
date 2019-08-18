#include <cstdio>
#include <vector>
#include <cstdlib>
#include <queue>
#include <algorithm>

int dis(int n, int s, int t, const std::vector<std::vector<std::pair<int, int>>>& edges) {
  std::vector<int> dis(n, -1);
  std::priority_queue<std::pair<int, int>> pq;
  pq.emplace(0, s);
  dis[s] = 0;
  while (!pq.empty()) {
    int d = -pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (dis[u] < d) continue;
    for (auto &e: edges[u]) {
      int v = e.first;
      int w = d + e.second;
      if (dis[v] == -1 || dis[v] > w) {
        dis[v] = w;
        pq.emplace(-w, v);
      }
    }
  }
  return dis[t];
}

int main() {
  int n, m, s, t, d;
  scanf("%d%d%d%d%d", &n, &m, &s, &t, &d);
  std::vector<std::vector<std::pair<int, int>>> edges_1(n);
  std::vector<std::vector<std::pair<int, int>>> edges_d(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c1, d1, c2, d2;
    scanf("%d%d%d%d%d%d", &u, &v, &c1, &d1, &c2, &d2);
    --u, --v;
    edges_1[u].emplace_back(v, c1);
    edges_1[v].emplace_back(u, c2);
    edges_d[u].emplace_back(v, c1 + (d - 1) * d1);
    edges_d[v].emplace_back(u, c2 + (d - 1) * d2);
  }
  --s, --t;
  printf("%d\n", std::min(dis(n, s, t, edges_1) + dis(n, t, s, edges_1), dis(n, s, t, edges_d) + dis(n, t, s, edges_d)));
  return 0;
}

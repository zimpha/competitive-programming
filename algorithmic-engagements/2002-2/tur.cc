#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<int>> edges(n);
  std::vector<int> deg(n);
  std::priority_queue<int> pq;
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    deg[y]++;
    edges[x].push_back(y);
  }
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) pq.push(-i);
  }
  std::vector<int> order;
  order.reserve(n);
  while (!pq.empty()) {
    int u = -pq.top();
    order.push_back(u);
    pq.pop();
    for (auto &v: edges[u]) {
      if (--deg[v] == 0) {
        pq.push(-v);
      }
    }
  }
  for (auto &x: order) printf("%d\n", x + 1);
  return 0;
}

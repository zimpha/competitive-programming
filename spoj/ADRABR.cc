#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    --s, --t;
    std::vector<std::vector<std::pair<int, int>>> edges(n);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      --u, --v;
      edges[u].emplace_back(v, w + 12);
      edges[v].emplace_back(u, w + 12);
    }
    std::vector<int64> dis(n, -1);
    std::vector<bool> mark(n);
    std::queue<int> queue;
    dis[s] = 0;
    queue.push(s);
    while (!queue.empty()) {
      int u = queue.front();
      mark[u] = 0;
      queue.pop();
      for (auto &&e: edges[u]) {
        int v = e.first, w = e.second;
        if (dis[v] == -1 || dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!mark[v]) mark[v] = 1, queue.push(v);
        }
      }
    }
    printf("%lld\n", dis[t]);
  }
  return 0;
}

#include <cstdio>
#include <queue>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> parent(n, -1);
  std::vector<std::vector<int>> edges(n);
  std::vector<int> deg(n);
  for (int i = 1; i < n + m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    deg[b]++;
    edges[a].push_back(b);
  }
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) queue.push_back(i);
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &v: edges[u]) {
      parent[v] = u;
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", parent[i] + 1);
  }
  return 0;
}

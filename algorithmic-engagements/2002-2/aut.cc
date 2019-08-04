#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

struct Edge {
  int u, v, w;
  bool operator < (const Edge &rhs) const {
    return w < rhs.w;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    edges.emplace_back();
    scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    edges[i].u;
    edges[i].v;
  }
  std::sort(edges.begin(), edges.end());
  std::vector<int> dsu(n);
  for (int i = 0; i < n; ++i) dsu[i] = i;

  std::function<int(int)> root = [&](int x) {
    if (dsu[x] != x) dsu[x] = root(dsu[x]);
    return dsu[x];
  };

  for (int i = 0, cnt = 0; i < m; ++i) {
    int u = root(edges[i].u - 1);
    int v = root(edges[i].v - 1);
    if (u != v) {
      dsu[u] = v;
      if (++cnt == n - 1) {
        printf("%d\n", edges[i].w);
      }
    }
  }
  return 0;
}

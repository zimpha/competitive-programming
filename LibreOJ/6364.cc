#include <cstdio>
#include <vector>
#include <functional>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<std::vector<int>> edges(n);
    for (int i = 2, p; i <= n; ++i) {
      scanf("%d", &p);
      edges[p - 1].push_back(i - 1);
      edges[i - 1].push_back(p - 1);
    }

    std::vector<int> value(n);
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      value[x - 1] = y;
    }

    std::vector<int> depth(n);

    std::function<void(int, int)> dfs = [&](int u, int p) {
      for (auto &v: edges[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        dfs(v, u);
      }
    };

    depth[k - 1] = 0;
    dfs(k - 1, -1);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      if (depth[i] % 2) ret ^= value[i];
    }
    if (ret == 0) puts("win");
    else puts("gg");
  }
  return 0;
}

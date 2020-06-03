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
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    std::vector<int> mark(n, -1), col(n, -1);
    int root = -1;
    for (int u = 0; u < n; ++u) {
      for (auto &v: edges[u]) if (col[v] != -1) {
        mark[col[v]] = v;
      }
      col[u] = 0;
      while (mark[col[u]] != -1) {
        adj[u].push_back(mark[col[u]]);
        ++col[u];
      }
      for (auto &v: edges[u]) if (col[v] != -1) {
        mark[col[v]] = -1;
      }
      if (col[u] == k - 1) root = u;
    }
    std::vector<std::vector<int>> tree(k);
    for (int i = 1; i < k; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }
    if (k > n) {
      puts("No");
      continue;
    }

    std::vector<int> p(k, -1);
    int label = k - 1;
    std::function<void(int, int)> dfs = [&](int u, int v) {
      p[u] = v;
      for (auto &x: tree[u]) if (p[x] == -1) {
        int y = adj[v][--label];
        dfs(x, y);
      }
    };

    dfs(0, root);
    puts("Yes");
    for (int i = 0; i < k; ++i) {
      printf("%d ", p[i] + 1);
    }
    puts("");
  }
  return 0;
}

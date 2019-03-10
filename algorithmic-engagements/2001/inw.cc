#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<int>> edges(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  std::vector<int> size(n);
  int ret = 0;
  std::function<void(int, int)> dfs = [&](int u, int p) {
    size[u] = 1;
    for (auto &&v: edges[u]) if (v != p) {
      dfs(v, u);
      size[u] += size[v];
    }
    ret = std::max(ret, (n - size[u]) * size[u]);
  };
  dfs(0, -1);
  printf("%d\n", ret);
  return 0;
}

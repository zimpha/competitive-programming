#include <cstdio>
#include <vector>
#include <functional>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, d;
    scanf("%d%d", &n, &d);
    std::vector<std::vector<int>> rank(n, {1});
    std::vector<int> dsu(n);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };

    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      u = root(u - 1);
      v = root(v - 1);
      std::vector<int> a(d + 1, -1), b(d + 1, -1);
      int min_u = -1, min_v = -1;
      for (auto &&x: rank[v]) if (x != -1) {
        if (min_v == -1 || x < min_v) min_v = x;
      }
      for (auto &&x: rank[u]) if (x != -1) {
        if (min_u == -1 || x < min_u) min_u = x;
      }
      for (int x = 0; x < rank[u].size() && x + 1 <= d; ++x) {
        if (rank[u][x] == -1) continue;
        a[x + 1] = std::max(rank[u][x], min_v + 1);
      }
      for (int x = 0; x < rank[v].size() && x + 1 <= d; ++x) {
        if (rank[v][x] == -1) continue;
        b[x + 1] = std::max(rank[v][x], min_u + 1);
      }
      for (int x = 0; x <= d; ++x) {
        if (a[x] == -1) a[x] = b[x];
        else if (b[x] != -1) a[x] = std::min(a[x], b[x]);
      }
      while (a.back() == -1) a.pop_back();
      dsu[u] = v;
      rank[v] = a;
    }
    int ret = -1;
    for (auto &&x: rank[root(0)]) if (x != -1) {
      if (ret == -1 || ret > x) ret = x;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

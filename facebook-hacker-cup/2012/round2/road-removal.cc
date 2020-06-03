#include <cstdio>
#include <functional>
#include <vector>
#include <set>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<int> u(m), v(m);
    std::vector<int> dsu(n);
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };
    for (int i = 0; i < n; ++i) dsu[i] = i;
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &u[i], &v[i]);
      if (u[i] >= k && v[i] >= k) {
        dsu[root(u[i])] = root(v[i]);
      }
    }
    std::vector<int> col(n);
    for (int i = 0; i < n; ++i) col[i] = root(i);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    int ret = 0;
    for (int i = 0; i < m; ++i) {
      if (col[u[i]] == col[v[i]]) continue;
      int x = root(col[u[i]]);
      int y = root(col[v[i]]);
      if (x != y) dsu[x] = y;
      else ++ret;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

struct edge_t {
  int u, v, w;
  bool operator < (const edge_t &rhs) const {
    return w < rhs.w;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<edge_t> e(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  }
  std::sort(e.begin(), e.end());
  std::vector<int> dsu(n);
  for (int i = 0; i < n; ++i) dsu[i] = i;
  std::function<int(int)> root = [&](int x) {
    if (x != dsu[x]) dsu[x] = root(dsu[x]);
    return dsu[x];
  };
  int64 ret = 0;
  for (auto &&x: e) {
    int u = root(x.u - 1);
    int v = root(x.v - 1);
    if (u != v) {
      ret += x.w;
      dsu[u] = v;
    }
  }
  printf("%lld\n", ret);
  return 0;
}

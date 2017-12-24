#include <cstdio>
#include <vector>

constexpr int N = 1e5 + 10;
constexpr int W = 1e5 + 10;

std::vector<int> ql[W], edges[W];
int dsu[N], size[N];

int root(int x) {
  if (x != dsu[x]) dsu[x] = root(dsu[x]);
  return dsu[x];
}

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m,  &q);
  std::vector<int> a(m), b(m);
  int mx = 0;
  for (int i = 0, x; i < m; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &x);
    edges[x].emplace_back(i);
    if (x > mx) mx = x;
  }
  std::vector<int> st(q), ret(q);
  for (int i = 0, x; i < q; ++i) {
    scanf("%d%d", &st[i], &x);
    ql[x].emplace_back(i);
    if (x > mx) mx = x;
  }
  for (int i = 0; i < n; ++i) {
    dsu[i] = i;
    size[i] = 1;
  }
  for (int it = mx; it >= 1; --it) {
    for (auto &&e: edges[it]) {
      int u = root(a[e]), v = root(b[e]);
      if (u != v) dsu[u] = v, size[v] += size[u];
    }
    for (auto &&q: ql[it]) {
      ret[q] = size[root(st[q])];
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}

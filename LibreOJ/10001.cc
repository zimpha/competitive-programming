#include <cstdio>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>

struct node {
  int l, r, t;
  bool operator < (const node& rhs) const {
    return r < rhs.r;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<node> s(m);
  std::vector<int> dsu(n + 1);
  std::vector<int> bit(n + 1);
  for (int i = 0; i <= n; ++i) dsu[i] = i;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].t);
  }
  std::sort(s.begin(), s.end());

  std::function<int(int)> root = [&](int x) {
    if (x != dsu[x]) dsu[x] = root(dsu[x]);
    return dsu[x];
  };

  auto add = [&](int x, int v) {
    for (; x <= n; x += ~x & x + 1) bit[x] += v;
  };

  auto get = [&](int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += bit[x];
    return r;
  };

  for (auto &e: s) {
    e.t -= get(e.r) - get(e.l - 1);
    for (int j = root(e.r); e.t > 0; j = root(j)) {
      add(j, 1);
      dsu[j] = root(j - 1);
      --e.t;
    }
  }
  printf("%d\n", get(n));
  return 0;
}

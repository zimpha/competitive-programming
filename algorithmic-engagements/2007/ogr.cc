#include <cstdio>
#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>

struct Limit {
  int l, r, idx;
};

int main() {
  int n, l, r, vm;
  scanf("%d%d%d%d", &n, &l, &r, &vm);
  std::vector<std::vector<Limit>> limit(vm + 1);
  for (int i = 0; i < n; ++i) {
    int x, y, v;
    scanf("%d%d%d", &x, &y, &v);
    x = std::max(x, l);
    y = std::min(y, r);
    v = std::min(v, vm);
    if (x < y) {
      limit[v].push_back((Limit){x - l, y - l, i});
    }
  }
  int m = r - l;
  std::vector<std::pair<int, int>> mx(m, {vm, vm});
  std::vector<int> f(m + 1), g(m + 1);
  
  std::function<int(std::vector<int>&, int)> next = [&](std::vector<int>& dsu, int x) {
    if (dsu[x] != x) dsu[x] = next(dsu, dsu[x]);
    return dsu[x];
  };

  for (int i = 0; i <= m; ++i) {
    f[i] = g[i] = i;
  }

  auto cover = [&](int l, int r, int v) {
    if (l >= r) return;
    for (int x = next(g, l); x < r; x = next(g, x + 1)) {
      g[x] = x + 1;
      mx[x].second = v;
    }
  };

  for (int v = 1; v <= vm; ++v) {
    for (auto &e: limit[v]) {
      for (int i = e.l; i < e.r; ) {
        int l = i, r = next(f, i);
        cover(l, std::min(r, e.r), v);
        if (r < e.r) {
          mx[r].first = v;
          f[r] = r + 1;
        }
        i = r + 1;
      }
    }
  }
  int sum = 0, best = 0, index = 0;
  std::vector<std::vector<int>> ri(vm + 1);
  std::vector<std::vector<int>> rs(vm + 1);
  for (int i = 0; i < m; ++i) {
    sum += mx[i].first;
    best += mx[i].first;
    ri[mx[i].first].push_back(i);
    rs[mx[i].first].push_back(mx[i].second - mx[i].first);
    assert(mx[i].second >= mx[i].first);
  }
  for (int v = 1; v <= vm; ++v) if (!ri[v].empty()) {
    for (int i = ri[v].size() - 2; i >= 0; --i) {
      rs[v][i] += rs[v][i + 1];
    }
    for (auto &e: limit[v]) {
      int l = std::lower_bound(ri[v].begin(), ri[v].end(), e.l) - ri[v].begin();
      int r = std::lower_bound(ri[v].begin(), ri[v].end(), e.r) - ri[v].begin();
      int delta = l == ri[v].size() ? 0 : rs[v][l];
      delta -= r == ri[v].size() ? 0 : rs[v][r];
      if (delta + sum > best || (delta + sum == best && e.idx < index)) {
        best = delta + sum;
        index = e.idx;
      }
    }
  }
  printf("%d\n", index + 1);
  return 0;
}

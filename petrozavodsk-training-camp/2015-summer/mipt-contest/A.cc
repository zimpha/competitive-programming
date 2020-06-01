#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>

using uint64 = unsigned long long;

const int N = 50000 + 10, M = N * 16 * 16 * 4;

std::pair<int, int> a[N];

namespace seg {
  int u[M], ls[M], rs[M], sz;
  void init() {
    u[0] = ls[0] = rs[0] = 0;
    sz = 1;
  }
  int ins(int o, int l, int r, int x) {
    int p = sz++;
    u[p] = u[o] + 1;
    ls[p] = ls[o]; rs[p] = rs[o];
    if (l + 1 == r) return p;
    int m = (l + r) >> 1;
    if (x < m) ls[p] = ins(ls[o], l, m, x);
    else rs[p] = ins(rs[o], m, r, x);
    return p;
  }
  int get(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) return u[o];
    int ret = 0, m = (l + r) >> 1;
    if (L < m) ret += get(ls[o], l, m, L, R);
    if (R > m) ret += get(rs[o], m, r, L, R);
    return ret;
  }
}

template <class T>
void merge(std::vector<T> &l, std::vector<T> &r, std::vector<T> &o) {
  o.reserve(l.size() + r.size());
  size_t x = 0, y = 0;
  while (x < l.size() && y < r.size()) {
    if (l[x] < r[y]) o.push_back(l[x++]);
    else o.push_back(r[y++]);
  }
  while (x < l.size()) o.push_back(l[x++]);
  while (y < r.size()) o.push_back(r[y++]);
}

int last[500000 + 10];

struct Fen {
  std::vector<int> xs;
  std::vector<std::vector<std::pair<int, int>>> u;
  std::vector<std::vector<int>> ys, rt;
  int nx;
  void build(int n) {
    xs.resize(n);
    for (int i = 0; i < n; ++i) {
      xs[i] = a[i].first;
      last[a[i].second] = -1;
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    nx = xs.size();
    u.resize(nx * 2);
    ys.resize(nx * 2);
    rt.resize(nx * 2);
    std::sort(a, a + n);
    for (int i = 0, j; i < n; i = j) {
      int x = std::lower_bound(xs.begin(), xs.end(), a[i].first) - xs.begin() + nx;
      for (j = i; j < n && a[i].first == a[j].first; ++j) {
        u[x].emplace_back(last[a[j].second], a[j].second);
        ys[x].emplace_back(a[j].second);
        last[a[j].second] = a[i].first;
      }
      std::sort(u[x].begin(), u[x].end());
      std::sort(ys[x].begin(), ys[x].end());
      ys[x].erase(std::unique(ys[x].begin(), ys[x].end()), ys[x].end());
      build_impl(x);
    }
    for (int i = nx - 1; i > 0; --i) {
      merge(u[i << 1], u[i << 1 | 1], u[i]);
      merge(ys[i << 1], ys[i << 1 | 1], ys[i]);
      ys[i].erase(std::unique(ys[i].begin(), ys[i].end()), ys[i].end());
      build_impl(i);
    }
  }
  int count(int x1, int x2, int y1, int y2, int ret = 0) {
    int l = std::lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
    int r = std::upper_bound(xs.begin(), xs.end(), x2) - xs.begin();
    for (l += nx, r += nx; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret += count_impl(l++, x1, y1, y2);
      if (r & 1) ret += count_impl(--r, x1, y1, y2);
    }
    return ret;
  }
  void build_impl(int o) {
    rt[o].resize(u[o].size());
    int r = 0;
    for (size_t i = 0; i < u[o].size(); ++i) {
      int y = std::lower_bound(ys[o].begin(), ys[o].end(), u[o][i].second) - ys[o].begin();
      r = seg::ins(r, 0, ys[o].size(), y);
      rt[o][i] = r;
    }
  }
  int count_impl(int o, int x, int y1, int y2) {
    int xi = std::lower_bound(u[o].begin(), u[o].end(), std::make_pair(x, 0)) - u[o].begin() - 1;
    y1 = std::lower_bound(ys[o].begin(), ys[o].end(), y1) - ys[o].begin();
    y2 = std::upper_bound(ys[o].begin(), ys[o].end(), y2) - ys[o].begin();
    if (xi < 0 || y1 >= y2) return 0;
    return seg::get(rt[o][xi], 0, ys[o].size(), y1, y2);
  }
} bit[2];

int main() {
  int n, q;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  seg::init();
  bit[0].build(n);
  for (int i = 0; i < n; ++i) {
    std::swap(a[i].first, a[i].second);
  }
  bit[1].build(n);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d ", bit[1].count(y1, y2, x1, x2));
    printf("%d\n", bit[0].count(x1, x2, y1, y2));
    fflush(stdout);
  }
  return 0;
}

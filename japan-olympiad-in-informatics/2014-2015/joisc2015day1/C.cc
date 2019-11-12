#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;
using uint = unsigned int;

constexpr int N = 1e5 + 10;
constexpr int64 inf = 1e18;

struct Node {
  int64 mx;
  int64 delta;
  void apply(int64 v) {
    mx += v;
    delta += v;
  }
} T[N * 4];

void build(int o, int l, int r) {
  T[o].delta = T[o].mx = 0;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m); 
  build(o << 1 | 1, m, r);
}

void push(int o) {
  if (T[o].delta) {
    T[o << 1].apply(T[o].delta);
    T[o << 1 | 1].apply(T[o].delta);
    T[o].delta = 0;
  }
}

void add(int o, int l, int r, int L, int R, int64 v) {
  if (L <= l && R >= r) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
}

void set(int o, int l, int r, int x, int64 v) {
  if (l + 1 == r) {
    T[o].mx = v;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (x < m) set(o << 1, l, m, x, v);
  else set(o << 1 | 1, m, r, x, v);
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
}

int64 get(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].mx;
  push(o);
  int m = (l + r) >> 1;
  int64 ret = -inf;
  if (L < m) ret = std::max(ret, get(o << 1, l, m, L, R));
  if (R > m) ret = std::max(ret, get(o << 1 | 1, m, r, L, R));
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> h(n), p(n), c(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &h[i], &p[i], &c[i]);
  }
  auto xs = h;
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  int m = xs.size();
  build(1, 0, m);
  std::vector<int64> f(n), g(n);
  for (int i = 0; i < n; ++i) {
    auto u = std::lower_bound(xs.begin(), xs.end(), h[i]) - xs.begin();
    auto mx = get(1, 0, m, 0, u + 1);
    f[i] = mx + p[i];
    set(1, 0, m, u, f[i]);
    if (u) add(1, 0, m, 0, u, -c[i]);
  }
  build(1, 0, m);
  for (int i = n - 1; i >= 0; --i) {
    auto u = std::lower_bound(xs.begin(), xs.end(), h[i]) - xs.begin();
    auto mx = get(1, 0, m, 0, u + 1);
    g[i] = mx + p[i];
    set(1, 0, m, u, g[i]);
    if (u) add(1, 0, m, 0, u, -c[i]);
  }
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = std::max(ret, f[i] + g[i] - p[i]);
  }
  printf("%lld\n", ret);
  return 0;
}

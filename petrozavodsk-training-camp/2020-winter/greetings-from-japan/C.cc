#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int64 inf = 1ll << 60;

template <class T>
class DynamicRMQ {
public:
  void build(int n, T init) {
    this->n = n;
    this->init = init;
    this->h = sizeof(int) * 8 - __builtin_clz(n);
    u.assign(n * 2, init);
  }
  void modify(int l, int r, const T& v) {// [l, r]
    l += n; r += n;
    push(l); push(r - 1);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) u[l] = std::max(u[l], v), ++l;
      if (r & 1) --r, u[r] = std::max(u[r], v);
    }
  }
  void update(int x) {
    if (u[x] != init) {
      u[x << 1] = std::max(u[x << 1], u[x]);
      u[x << 1 | 1] = std::max(u[x << 1 | 1], u[x]);
      u[x] = init;
    }
  }
  void push(int x) {
    for (int i = h; i > 0; --i) update(x >> i);
  }
  T get(int x) {
    push(x + n);
    return u[x + n];
  }
private:
  std::vector<T> u;
  int n, h;
  T init;
};

int main() {
  int n, m, x, y;
  scanf("%d%d%d%d", &n, &m, &x, &y);
  std::vector<int> l(m), r(m), c(m);
  std::vector<int> xs;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &c[i], &l[i], &r[i]);
    --l[i], --c[i];
    xs.push_back(l[i]);
    xs.push_back(r[i]);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  std::vector<std::vector<int>> segs(xs.size());
  for (int i = 0; i < m; ++i) {
    l[i] = std::lower_bound(xs.begin(), xs.end(), l[i]) - xs.begin();
    r[i] = std::lower_bound(xs.begin(), xs.end(), r[i]) - xs.begin();
    segs[r[i]].push_back(i);
  }

  std::vector<DynamicRMQ<int64>> f(3), g(3);
  DynamicRMQ<int64> h;
  for (int i = 0; i < 3; ++i) {
    f[i].build(xs.size(), -inf);
    g[i].build(xs.size(), -inf);
  }
  h.build(xs.size(), 0);
  int64 ret = 0;
  for (size_t r = 0; r < xs.size(); ++r) for (auto i: segs[r]) {
    int64 now = std::max<int64>(0, h.get(l[i]) + int64(xs[r] - xs[l[i]]) * x);
    for (int j = 0; j < 3; ++j) {
      if (j == c[i]) now = std::max(now, f[j].get(l[i]) + (int64)xs[r] * x);
      else now = std::max(now, g[j].get(l[i]) + (int64)xs[r] * x + (int64)xs[l[i]] * (y + x));
    }
    ret = std::max(ret, now);
    h.modify(r, xs.size() - 1, now);
    f[c[i]].modify(l[i], r, now - (int64)xs[r] * x);
    g[c[i]].modify(l[i], r, now - (int64)xs[r] * (x * 2 + y));
  }
  printf("%lld\n", ret);
  return 0;
}

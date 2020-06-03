#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int64> a(n + 1, 0), b(n + 1, 0);
  std::vector<int64> xs(n + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    a[i] += a[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &b[i]);
    b[i] += b[i - 1];
    xs[i] = b[i] - a[i];
  }
  std::vector<std::vector<int>> query(n + 1);
  std::vector<int64> ret(q + 1);
  std::vector<int> l(q + 1), r(q + 1);
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d", &l[i], &r[i]);
    query[l[i]].push_back(+i);
    if (r[i] < n) query[r[i] + 1].push_back(-i);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  int m = xs.size();
  std::vector<int64> sum(m + 1), cnt(m + 1);

  auto add = [&] (int x, int64 v) {
    for (; x <= m; x += ~x & x + 1) sum[x] += v, cnt[x] += 1;
  };

  auto get_s = [&] (int x, int64 r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += sum[x];
    return r;
  };

  auto get_c = [&] (int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += cnt[x];
    return r;
  };

  sum.assign(m + 1, 0); cnt.assign(m + 1, 0);
  for (int i = n; i >= 1; --i) {
    // b[i] - b[l] >= a[i] - a[l] => b[i] - a[i] >= b[l] - a[l]
    auto p = std::lower_bound(xs.begin(), xs.end(), b[i] - a[i]) - xs.begin();
    add(p, b[i]);
    for (auto e: query[i]) {
      int idx = std::abs(e), sign = e > 0 ? 1 : -1;
      auto q = std::lower_bound(xs.begin(), xs.end(), b[l[idx] - 1] - a[l[idx] - 1]) - xs.begin();
      ret[idx] += sign * (get_s(m) - get_s(q - 1));
      ret[idx] -= sign * (get_c(m) - get_c(q - 1)) * b[l[idx] - 1];
    }
  }
  sum.assign(m + 1, 0); cnt.assign(m + 1, 0);
  for (int i = n; i >= 1; --i) {
    // b[i] - b[l] < a[i] - a[l] => b[i] - a[i] < b[l] - a[l]
    auto p = std::lower_bound(xs.begin(), xs.end(), b[i] - a[i]) - xs.begin();
    add(p, a[i]);
    for (auto e: query[i]) {
      int idx = std::abs(e), sign = e > 0 ? 1 : -1;
      auto q = std::lower_bound(xs.begin(), xs.end(), b[l[idx] - 1] - a[l[idx] - 1]) - xs.begin();
      ret[idx] += sign * get_s(q - 1);
      ret[idx] -= sign * get_c(q - 1) * a[l[idx] - 1];
    }
  }
  for (int i = 1; i <= q; ++i) printf("%lld\n", ret[i]);
  return 0;
}

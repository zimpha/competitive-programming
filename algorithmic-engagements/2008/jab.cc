#include <cstdio>
#include <vector>
#include <algorithm>

const int inf = 1e9;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::pair<int, int>> a(n), b(m);
  std::vector<int> ys(n + m);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    ys[i] = a[i].second;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &b[i].first, &b[i].second);
    ys[i + n] = b[i].second;
  }
  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  int ret = inf;
  int s = ys.size();
  std::vector<int> u(s, inf), v(s, inf);
  for (int i = 0, j = 0; j < m; ++j) {
    while (i < n && a[i].first <= b[j].first) {
      auto y = std::lower_bound(ys.begin(), ys.end(), a[i].second) - ys.begin();
      auto ku = a[i].second - a[i].first;
      auto kv = -a[i].second - a[i].first;
      for (int k = y; k >= 0; k -= ~k & k + 1) u[k] = std::min(u[k], ku);
      for (int k = y; k < s; k += ~k & k + 1) v[k] = std::min(v[k], kv);
      ++i;
    }
    auto y = std::lower_bound(ys.begin(), ys.end(), b[j].second) - ys.begin();
    auto ku = inf, kv = inf;
    for (int k = y; k < s; k += ~k & k + 1) ku = std::min(u[k], ku);
    for (int k = y; k >= 0; k -= ~k & k + 1) kv = std::min(v[k], kv);
    ret = std::min(ret, b[j].first - b[j].second + ku);
    ret = std::min(ret, b[j].first + b[j].second + kv);
  }
  u.assign(s, inf); v.assign(s, inf);
  for (int i = n - 1, j = m - 1; j >= 0; --j) {
    while (i >= 0 && a[i].first >= b[j].first) {
      auto y = std::lower_bound(ys.begin(), ys.end(), a[i].second) - ys.begin();
      auto ku = a[i].second + a[i].first;
      auto kv = -a[i].second + a[i].first;
      for (int k = y; k >= 0; k -= ~k & k + 1) u[k] = std::min(u[k], ku);
      for (int k = y; k < s; k += ~k & k + 1) v[k] = std::min(v[k], kv);
      --i;
    }
    auto y = std::lower_bound(ys.begin(), ys.end(), b[j].second) - ys.begin();
    auto ku = inf, kv = inf;
    for (int k = y; k < s; k += ~k & k + 1) ku = std::min(u[k], ku);
    for (int k = y; k >= 0; k -= ~k & k + 1) kv = std::min(v[k], kv);
    ret = std::min(ret, -b[j].first - b[j].second + ku);
    ret = std::min(ret, -b[j].first + b[j].second + kv);
  }
  printf("%d\n", ret);
  return 0;
}

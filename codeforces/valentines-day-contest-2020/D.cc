#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, nx, ny;
  scanf("%d", &n);
  scanf("%d", &nx);
  std::vector<std::pair<int, int>> xs(nx);
  for (int i = 0; i < nx; ++i) scanf("%d%d", &xs[i].first, &xs[i].second);
  scanf("%d", &ny);
  std::vector<std::pair<int, int>> ys(ny);
  for (int i = 0; i < ny; ++i) scanf("%d%d", &ys[i].first, &ys[i].second);
  int mid = sqrt(n) + 1;
  if (mid > n) mid = n;
  std::vector<int> bad(mid + 1, 0);
  std::vector<std::pair<int, int>> ts;

  auto check = [&](int T, int l, int r, int e) {
    if (l > r) return false;
    // l <= T * (2k - e) <= r, 1 <= k
    r = (r / T + e) / 2;
    l = ((l + T - 1) / T + e + 1) / 2;
    return l <= r;
  };

  auto handle = [&](int k, int l, int r, int e) {
    // l <= (2k - e) * T <= r
    r = r / (2 * k - e);
    l = (l + 2 * k - e - 1) / (2 * k - e);
    if (l <= mid) l = mid + 1;
    if (l <= r) ts.emplace_back(l, r);
  };

  for (int T = 1; T <= mid; ++T) {
    if (xs[0].first != 1) bad[T] |= check(T, 1, xs[0].first - 1, 1);
    for (int i = 1; i < nx && !bad[T]; ++i) bad[T] |= check(T, xs[i - 1].second + 1, xs[i].first - 1, 1);
    if (xs.back().second != n) bad[T] |= check(T, xs.back().second + 1, n, 1);

    if (ys[0].first != 1) bad[T] |= check(T, 1, ys[0].first - 1, 0);
    for (int i = 1; i < ny && !bad[T]; ++i) bad[T] |= check(T, ys[i - 1].second + 1, ys[i].first - 1, 0);
    if (ys.back().second != n) bad[T] |= check(T, ys.back().second + 1, n, 0);
  }

  for (int k = 1; k <= mid; ++k) {
    if (xs[0].first != 1) handle(k, 1, xs[0].first - 1, 1);
    for (int i = 1; i < nx; ++i) handle(k, xs[i - 1].second + 1, xs[i].first - 1, 1);
    if (xs.back().second != n) handle(k, xs.back().second + 1, n, 1);

    if (ys[0].first != 1) handle(k, 1, ys[0].first - 1, 0);
    for (int i = 1; i < ny; ++i) handle(k, ys[i - 1].second + 1, ys[i].first - 1, 0);
    if (ys.back().second != n) handle(k, ys.back().second + 1, n, 0);
  }

  int ret = 0;
  for (int i = 1; i <= mid; ++i) ret += bad[i];
  if (ts.size()) {
    std::sort(ts.begin(), ts.end());
    int l = ts[0].first, r = ts[0].second;
    for (auto &e: ts) {
      if (e.first <= r + 1) r = std::max(r, e.second);
      else {
        ret += r - l + 1;
        l = e.first, r = e.second;
      }
    }
    ret += r - l + 1;
  }
  printf("%d\n", n - ret);
  return 0;
}

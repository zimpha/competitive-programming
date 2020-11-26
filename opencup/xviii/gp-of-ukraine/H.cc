#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

int main() {
  int n, m, k, d;
  scanf("%d%d%d%d", &n, &m, &k, &d);
  std::vector<int> c(m), a(k);
  for (int i = 0; i < m; ++i) scanf("%d", &c[i]);
  for (int i = 0; i < k; ++i) scanf("%d", &a[i]);
  std::sort(c.begin(), c.end());
  std::sort(a.begin(), a.end());

  auto count = [&](int l, int r) -> int { // l <= x < r
    return std::lower_bound(a.begin(), a.end(), r) - std::lower_bound(a.begin(), a.end(), l);
  };

  int cnt = m;
  if (2 + d <= n) cnt = count(2, 2 + d);
  for (auto &x: a) {
    if (x - 1 + d <= n) cnt = std::min(cnt, count(x - 1, x - 1 + d));
    if (x + d <= n) cnt = std::min(cnt, count(x, x + d));
    if (x + 1 + d <= n) cnt = std::min(cnt, count(x + 1, x + 1 + d));
  }
  i64 ret = 0;
  if (cnt == 0) {
    for (auto &x: c) ret += x;
    ret -= c[0];
    int last = 1;
    for (auto &x: a) {
      if (x - last > d) ret += c[0];
      last = x;
    }
    if (n - last > d) ret += c[0];
  } else {
    while (!c.empty() && cnt) {
      c.pop_back();
      --cnt;
    }
    for (auto &x: c) ret += x;
  }
  printf("%lld\n", ret);
  return 0;
}

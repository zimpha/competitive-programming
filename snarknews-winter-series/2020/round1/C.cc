#include <cstdio>
#include <algorithm>
#include <vector>

const long long base = 1e12;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> s(n);
  for (int i = 0; i < n; ++i) scanf("%d%d", &s[i].first, &s[i].second);
  std::sort(s.begin(), s.end());
  long long xa = s[n / 2].first + 1, ya = s[n / 2].second - base;
  long long xb = s[n / 2].first - 1, yb = s[n / 2].second + base;
  if (n % 2 == 0) --yb;
  auto dx = xb - xa, dy = yb - ya;
  auto xc = xa - dy, yc = ya + dx;
  auto xd = xa + dy, yd = ya - dx;
  printf("%lld %lld\n%lld %lld\n", xc, yc, xd, yd);
  return 0;
}

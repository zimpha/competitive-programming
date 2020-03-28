#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  std::sort(a.begin(), a.end());
  int64 now = std::max(a.back().first, a.back().second);
  for (int i = n - 2; i >= 0; --i) {
    now += a[i + 1].first - a[i].first;
    if (now < a[i].second) now = a[i].second;
  }
  printf("%lld\n", now + a[0].first);
  return 0;
}

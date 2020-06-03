#include <cstdio>
#include <queue>
#include <tuple>
#include <utility>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = a[i].first;
  }
  std::sort(a.rbegin(), a.rend());
  double prob = 1, ret = 0;
  int cnt = 0;
  for (int mx = a[0].first, l = 0, r = 0; mx; --mx) {
    while (r < n && a[r].first == mx) ++r;
    for (int i = l; i < r; ++i) {
      prob /= double(mx + 1) / (a[i].second + 1);
      if (cnt & 1) ret += prob / (a[i].second + 1);
      cnt ^= 1;
      prob *= double(mx) / (a[i].second + 1);
    }
  }
  if (cnt & 1) ret += prob;
  printf("%.15f\n", ret);
  return 0;
}

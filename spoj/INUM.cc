#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  std::sort(a.begin(), a.end());
  std::vector<std::pair<int64, int64>> g;
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && a[i] == a[j]; ++j);
    g.emplace_back(a[i], j - i);
  }
  auto sum = [&](int64 x) {
    return x * (x - 1) / 2;
  };
  if (g.size() == 1) {
    printf("%lld %lld\n", sum(g[0].second), sum(g[0].second));
  } else {
    int64 ret = 0, diff = -1;
    for (auto &&e: g) {
      if (e.second > 1) diff = 0;
      ret += sum(e.second);
    }
    for (size_t i = 1; i < g.size(); ++i) {
      int64 d = g[i].first - g[i - 1].first;
      if (diff == -1 || d < diff) {
        ret = 0;
        diff = d;
      }
      if (d == diff) ret += g[i].second * g[i - 1].second;
    }
    printf("%lld %lld\n", ret, g[0].second * g.back().second);
  }
  return 0;
}

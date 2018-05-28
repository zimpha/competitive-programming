#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    --m;
    std::vector<int64> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }
    std::vector<int64> values;
    int count = 0;
    for (int i = 1; i < n - 1; ++i) {
      int64 sum = 0;
      for (int j = i; j < n - 1; ++j) {
        sum += a[j];
        if (i <= m && m <= j) {
          values.emplace_back(sum - a[m]);
        } else {
          count += sum > 0;
        }
      }
    }
    std::sort(values.begin(), values.end());
    int64 ret = 0;
    for (size_t i = 0; i < values.size(); ++i) {
      int64 l = 0, r = 0;
      if (i == 0 || values[i] != values[i - 1]) {
        if ((count + values.size() - i) & 1) {
          l = std::max(-a[m], -values[i] + 1);
          if (i == 0) r = a[m];
          else r = std::min(a[m], -values[i - 1]);
          if (l <= r) ret += r - l + 1;
        }
      }
    }
    if ((count & 1) && values.size()) {
      int64 l = -a[m], r = std::min(a[m], -values.back());
      if (l <= r) ret += r - l + 1;
    }
    printf("Case #%d: %lld\n", cas, ret);
  }
  return 0;
}
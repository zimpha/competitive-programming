#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 left = 0, right = 0;
    int r, b, n;
    scanf("%d%d%d", &r, &b, &n);
    std::vector<int64> m(n), s(n), p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld%lld%lld", &m[i], &s[i], &p[i]);
      if (s[i] * m[i] + p[i] > right) right = s[i] * m[i] + p[i];
    }
    while (left < right) {
      int64 mid = (left + right - 1) >> 1;
      std::vector<int64> sum(n);
      for (int i = 0; i < n; ++i) if (mid >= p[i]) {
        sum[i] = std::min(m[i], (mid - p[i]) / s[i]);
      }
      std::sort(sum.begin(), sum.end(), std::greater<int64>());
      int64 total = 0;
      for (int i = 0; i < r; ++i) total += sum[i];
      if (total >= b) right = mid;
      else left = mid + 1;
    }
    printf("Case #%d: %lld\n", cas, left);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    int64 m;
    scanf("%d%lld", &n, &m);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    int x = n / 2, y = n - x;
    std::vector<int64> s(1 << x);
    int64 ret = 0;
    for (int mask = 0; mask < (1 << x); ++mask) {
      int64 r = 0;
      for (int i = 0; i < x; ++i) {
        if (mask >> i & 1) r += a[i];
      }
      s[mask] = r;
      if (r <= m) ret = std::max(ret, r);
    }
    std::sort(s.begin(), s.end());
    for (int mask = 0; mask < (1 << y); ++mask) {
      int64 r = 0;
      for (int i = 0; i < y; ++i) {
        if (mask >> i & 1) r += a[i + x];
      }
      if (r <= m) ret = std::max(ret, r);
      auto it = std::upper_bound(s.begin(), s.end(), m - r);
      if (it != s.begin()) ret = std::max(ret, *(it - 1) + r);
    }
    printf("%lld\n", ret);
  }
  return 0;
}

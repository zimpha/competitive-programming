#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

const int64 inf = 1ll << 60;

int main() {
  int n;
  int64 k;
  scanf("%d%lld", &n, &k);
  std::vector<int64> a(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);

  std::sort(a.begin(), a.end());
  auto count = [&](int64 bound) {
    int64 ret = 0;
    for (int i = 0; i + 1 < n; ++i) {
      if (a[i] < 0) {
        if (a[i] * a.back() > bound) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
          int m = (l + r - 1) >> 1;
          if (a[i] * a[m] <= bound) r = m;
          else l = m + 1;
        }
        ret += n - l;
      } else {
        if (a[i] * a[i + 1] > bound) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
          int m = (l + r + 1) >> 1;
          if (a[i] * a[m] <= bound) l = m;
          else r = m - 1;
        }
        ret += l - i;
      }
    }
    return ret;
  };

  int64 left = 0, right = 2 * inf;
  while (left < right) {
    int64 mid = (left + right - 1) >> 1;
    if (count(mid - inf) >= k) right = mid;
    else left = mid + 1;
  }
  printf("%lld\n", left - inf);
  return 0;
}

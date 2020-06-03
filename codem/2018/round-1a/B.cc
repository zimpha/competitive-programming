#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> a(n);
  std::vector<int64> b(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%lld", &b[i]);
  int l = 0;
  int64 sum = 0, ret = 0;
  for (int i = n - 1; i >= 0; --i) {
    sum += a[i];
    if (b[i]) {
      int64 provide = std::min(b[i], sum);
      b[i] -= provide;
      sum -= provide;
      while (b[i] && l < i) {
        int64 provide = std::min(b[i], a[l]);
        ret += provide * (l + i);
        a[l] -= provide;
        b[i] -= provide;
        if (!a[l]) ++l;
      }
    }
    ret += sum;
  }
  printf("%lld\n", ret);
  return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  int64 s2 = 0;
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = std::max(ret, (int64)s2 * sum);
    sum -= a[i];
    s2 += a[i] * a[i];
  }
  printf("%lld\n", ret);
  return 0;
}

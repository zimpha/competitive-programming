#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::sort(a.begin(), a.end());
  int64 ret = 0;
  for  (int i = 0; i < n; ++i) {
    ret += std::abs(a[i] - a[n / 2]);
  }
  printf("%lld\n", ret);
  return 0;
}

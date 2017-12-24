#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }
  std::sort(h.begin(), h.end());
  std::vector<int64> sum(n);
  for (int i = 0; i < n; ++i) {
    sum[i] = h[i];
    if (i) sum[i] += sum[i - 1];
  }
  int64 ret = sum.back();
  for (int i = 0; i < n; ++i) {
    ret = std::min(ret, sum.back() - (int64)(n - i) * h[i]);
  }
  printf("%lld\n", ret);
  return 0;
}

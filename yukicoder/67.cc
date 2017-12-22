#include <cmath>
#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  int64 k;
  scanf("%lld", &k);
  double left = 0, right = 1e9;
  for (int it = 0; it < 100; ++it) {
    double mid = (left + right) * 0.5;
    int64 cnt = 0;
    for (auto &&e: a) {
      cnt += floor(e / mid);
    }
    if (cnt >= k) left = mid;
    else right = mid;
  }
  printf("%.20f\n", left);
  return 0;
}

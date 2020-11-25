#include <cmath>
#include <cstdio>
#include <vector>

const double pi = acos(-1.0);

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> r(n);
  for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
  double left = 0, right = 1e9;
  for (int it = 0; it < 100; ++it) {
    double mid = (left + right) * 0.5;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
      double ca = mid / (r[i] * r[i]) - 1;
      double a = acos(ca);
      if (mid >= r[i] * r[i] * 2) a = 0;
      sum += a;
    }
    if (sum >= pi * 2) left = mid;
    else right = mid;
  }
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    if (left < r[i] * r[i] * 2) {
      double a = acos(left / (r[i] * r[i]) - 1);
      ret += r[i] * r[i] * (a + sin(a));
    }
  }
  printf("%.10f\n", ret);
  return 0;
}

#include <cmath>
#include <cstdio>

double calc(double a, double va, double b, double vb, double x) {
  return x * vb * b / sqrt(x * x * (va * va - vb * vb) + a * a * va * va);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    double h, a[3], v[3];
    scanf("%lf", &h);
    for (int i = 0; i < 3; ++i) scanf("%lf", a + i);
    for (int i = 0; i < 3; ++i) scanf("%lf", v + i);
    double left = 0, right = h;
    for (int it = 0; it < 100; ++it) {
      double mid = (left + right) * 0.5;
      double val = mid, now = mid;
      for (int i = 1; i < 3; ++i) {
        now = calc(a[i - 1], v[i - 1], a[i], v[i], now);
        val += now;
      }
      if (val < h) left = mid;
      else right = mid;
    }
    double now = left;
    double ret = hypot(now, a[0]) / v[0];
    for (int i = 1; i < 3; ++i) {
      now = calc(a[i - 1], v[i - 1], a[i], v[i], now);
      ret += hypot(now, a[i]) / v[i];
    }
    printf("%.10f\n", ret);
  }
  return 0;
}

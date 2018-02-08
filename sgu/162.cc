#include <cstdio>
#include <cmath>

int main() {
  double a, b, c, d, e, f;
  scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &f, &e, &d);
  a = a * a;
  b = b * b;
  c = c * c;
  d = d * d;
  e = e * e;
  f = f * f;
  printf("%.4f\n", sqrt(a * d * (b + c + e + f - a - d) + b * e * (a + c + d + f - b - e) + c * f * (a + b + d + e - c - f) - a * b * f - b * c * d - c * a * e - d * e * f) / 12);
    return 0;
}


#include <cmath>
#include <cstdio>

int main() {
  double a[6], b[6];
  double left = 0, right = acos(-1.0) / 2;
  for (int it = 0; it < 50; ++it) {
    a[0] = (left + right) / 2;
    b[0] = (50 * sqrt(2) - 50) * tan(a[0]);
    double len = b[0];
    for (int i = 1; i < 6; ++i) {
      a[i] = asin((1 - 0.1 * i) * sin(a[0]));
      b[i] = 10 * tan(a[i]);
      len += b[i];
    }
    if (len > 50 * sqrt(2)) right = a[0];
    else left = a[0];
  }
  double ret = 0;
  for (int i = 0; i < 6; ++i) {
    ret += b[i] / sin(a[i]) / (10 - i);
  }
  printf("%.10f\n", ret);
  return 0;
}

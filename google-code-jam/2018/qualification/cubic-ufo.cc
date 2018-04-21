#include <cmath>
#include <cstdio>
#include <algorithm>

struct point {
  double x, y, z;
  point() { }
  point(double x, double y, double z): x(x), y(y), z(z) {}

  point rotatex(double ang) {
    return {x, y * cos(ang) - z * sin(ang), y * sin(ang) + z * cos(ang)};
  }
  point rotatey(double ang) {
    return {x * cos(ang) - z * sin(ang), y, x * sin(ang) + z * cos(ang)};
  }
  point rotatez(double &ang) {
    return {x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang), z};
  }
};

const double pi = acos(-1);

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    point p0(.5, 0., 0.);
    point p1(0., .5, 0.);
    point p2(0., 0., .5);
    printf("Case #%d:\n", cas);
    double A;
    scanf("%lf", &A);
    double ang0 = asin(std::min(A, sqrt(2)) / sqrt(2));
    ang0 -= pi / 4;
    double ang1 = asin(std::max(A, sqrt(2)) / sqrt(3));
    ang1 -= asin(sqrt(2) / sqrt(3));
    p0 = (p0.rotatex(ang0)).rotatez(ang1);
    p1 = (p1.rotatex(ang0)).rotatez(ang1);
    p2 = (p2.rotatex(ang0)).rotatez(ang1);
    printf("%.15f %.15f %.15f\n", p0.x, p0.y, p0.z);
    printf("%.15f %.15f %.15f\n", p1.x, p1.y, p1.z);
    printf("%.15f %.15f %.15f\n", p2.x, p2.y, p2.z);
  }
  return 0;
}

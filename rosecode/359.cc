#include <bits/stdc++.h>

struct point {
  double x, y;
  point(double _x = 0, double _y = 0): x(_x), y(_y) {}
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const double &rhs) const {
    return point(x * rhs, y * rhs);
  }
  point operator / (const double &rhs) const {
    return point(x / rhs, y / rhs);
  }
  double norm() const {
    return hypot(x, y);
  }
};

point rot(const point &P, double cost, double sint) {
  double x=P.x,y=P.y;
  return point(x*cost-y*sint,x*sint+y*cost);
}

point cross(point &A, double ra, point &B, double rb) {
  double d = (A - B).norm();
  double ct = (ra * ra + d * d - rb * rb) / (2 * ra * d);
  double st = sqrt(1. - ct * ct);
  point v = (B - A) / (B - A).norm() * ra;
  return A + rot(v, ct, st);
}
double run(double a, double b, double c) {
  double left = 0, right = a + b;
  for (int it = 0; it < 1000; ++it) {
    double mid = (left + right) * 0.5;
    point A(-mid / 2, 0), B(mid / 2, 0), C(0, mid * sqrt(3) / 2);
    point O = cross(A, a, B, b);
    if ((O - C).norm() <= c) left = mid;
    else right = mid;
  }
  return (left + right) * 0.5;
}

int main() {
  std::cout.precision(20);
  std::cout << run(3, 4, 5) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

bool cmp(long x1, long y1, long x2, long y2) {
  return x1 < x2 || (x1 == x2 && y1 < y2);
}

double perimeter(long x1, long y1, long x2, long y2, double upp) {
  long x3 = 5 - x1 - x2, y3 = -y1 - y2;
  if (!cmp(x1, y1, x2, y2) || !cmp(x2, y2, x3, y3)) return 0;
  if (x3 * x3 + y3 * y3 != x1 * x1 + y1 * y1) return 0;
  double ret = hypot(x1 - x2, y1 - y2) + hypot(x1 - x3, y1 - y3) + hypot(x2 - x3, y2 - y3);
  if (ret > upp) ret = 0;
  else {
    std::cout << '(' << x1 << ' ' << y1 << "), (" << x2 << ' ' << y2 << "), (" << x3 << ' ' << y3 << ")" << std::endl;
  }
  return ret;
}

// x1 + x2 + x3 = 5, y1 + y2 + y3 = 0
// x1^2 + y1^2 = x2^2 + y2^2 = x3^2 + y3^2
// => 4((x1-5)^2+y1^2)*x2^2 + 4(x1-5)((x1-5)^2+y1^2)*x2 + (x1-5)^4-2(x1^2+10x1-25)y1^2-3y1^4=0
double run(long n) {
  double ret = 0;
  for (long x = -n / 3 - 5; x <= 1; ++x) {
    double upp = std::min(n / 3.0 - abs(x), sqrt(x * (3 * x - 20) + 25));
    for (long y = 0; y <= upp; ++y) {
      if ((x * x + y * y) % 5) continue;
      long a = (x - 5) * (x - 5) + y * y;
      long delta = a * (3 * x * x + 10 * x + 3 * y * y - 25);
      long sqd = sqrt(delta);
      if (delta != sqd * sqd) continue;
      long val = -(x - 5) * a - y * sqd;
      if (val % (a * 2) != 0) continue;
      long x2 = val / a / 2, y2 = sqrt(x * x + y * y - x2 * x2);
      if (x * x + y * y != x2 * x2 + y2 * y2) continue;
      ret += perimeter(x, y, x2, y2, n);
      if (y) ret += perimeter(x, -y, x2, y2, n);
      if (y2) ret += perimeter(x, y, x2, -y2, n);
      if (y && y2) ret += perimeter(x, -y, x2, -y2, n);
    }
  }
  return ret;
}

int main() {
  std::cout << std::fixed << std::setprecision(20);
  std::cout << run(50) << std::endl;
  std::cout << run(100000) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

void exgcd(long a, long b, long &g, long &x, long &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

long mod_inv(long a, long m) {
  long d, x, y;
  exgcd(a, m, d, x, y);
  return d == 1 ? (x % m + m) % m : -1;
}

long run(long n) {
  const int delta = 20;
  double peri = 0, radius = 0;
  for (long x1 = std::max(sqrt(n * n / 2) - 1, 0.); x1 <= n; ++x1) {
    long y1 = long(sqrt(n * n - x1 * x1));
    for (long x2 = x1 + 1; x2 <= x1 + delta && x2 <= n; ++x2) {
      long y2 = long(sqrt(n * n - x2 * x2));
      long x = x1 + x2, y = y1 + y2;
      if (std::__gcd(x, y) != 1) continue;
      long dx = mod_inv(y % x, x);
      long dy = (dx * y - 1) / x;
      double c = hypot(x, y);
      double a = hypot(dx, dy);
      double b = hypot(x - dx, y - dy);
      if (a + b + c > peri) {
        peri = a + b + c;
        radius = a * b * c / 2;
      }
    }
  }
  std::cout << peri << ' ' << radius << std::endl;
  return round(radius / n);
}

int main() {
  std::cout << run(5) << std::endl;
  std::cout << run(10) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(10000000) << std::endl;
  return 0;
}

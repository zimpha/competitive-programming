#include <bits/stdc++.h>

double eps = 1e-20;

double s(double x) {
  double n = floor(x);
  return std::min(x - n, n + 1 - x);
}

double blanc(double x) {
  double n = 1, r = 0;
  for (; ;) {
    double y = s(n * x) / n;
    if (eps > y) break;
    n *= 2;
    r += y;
  }
  return r;
}

double circle(double x) {
  return 0.5 - sqrt(x * (0.5 - x));
}

double solve(double l, double r) {
  for (int i = 0; i < 100; ++i) {
    double m = (l + r) * 0.5;
    double f = blanc(l) - circle(l);
    double g = blanc(r) - circle(r);
    double h = blanc(m) - circle(m);
    if (f * h < 0) r = m;
    else if (g * h < 0) l = m;
  }
  return (l + r) / 2;
}

double run() {
  double l = solve(0, 0.25), r = 0.5;
  double step = 1e-5, ret = 0;
  for (double x = l; x <= r; x += step) {
    ret += (blanc(x) - circle(x)) * step;
  }
  return ret;
}

int main() {
  std::cout.precision(8);
  std::cout << run() << std::endl;
  return 0;
}

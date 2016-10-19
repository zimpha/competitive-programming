#include <bits/stdc++.h>

double calc(double k) {
  double r1 = (k + 0.5) / k, r2 = (k - 0.5) / k;
  if (r1 < sqrt(2) / k) return 0;
  double t1 = sqrt(k * k + k - 0.75) / k, t2 = sqrt(k * k - k - 0.75) / k;
  double a1 = t1 / k - 1 / k / k, a2 = t2 / k - 1 / k / k;
  double b1 = atan2(t1, 1 / k) - atan2(1 / k, t1);
  double b2 = atan2(t2, 1 / k) - atan2(1 / k, t2);
  double c1 = r1 * r1 * b1 / 2, c2 = r2 * r2 * b2 / 2;
  if (r2 < sqrt(2) / k) return c1 - a1;
  else return (c1 - a1) - (c2 - a2);
}

double run(int n) {
  double ret = 0;
  for (int k = 1; k <= n; ++k) {
    ret += calc(k) * k;
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(10) << std::endl;
  std::cout << run(100000) << std::endl;
  return 0;
}

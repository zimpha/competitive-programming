#include <bits/stdc++.h>

double S(double l, double g, double d) {
  long s = 0;
  for (int m = 0; ; ++m) {
    long low = ceil((d + m) / l);
    long upp = floor((d + g + m) / l);
    if (low <= upp) {
      s = low;
      break;
    }
  }
  return s * l;
}

double cost(std::vector<int> &p, double g, double d) {
  if (g + d >= 1) return 0;
  double ret = 0;
  for (auto &&x: p) ret += S(sqrt(1.0 / x), g, d);
  return ret;
}

double M(int n, double g) {
  std::vector<int> mark(n + 1), p;
  for (int i = 2; i <= n; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j <= n; j += i) mark[j] = 1;
  }
  double left = 0, right = 1 - g;
  for (int i = 0; i < 100; ++i) {
    double mid1 = left + (right - left) / 3;
    double mid2 = right - (right - left) / 3;
    double val1 = cost(p, g, mid1);
    double val2 = cost(p, g, mid2);
    if (val1 < val2) left = mid1;
    else right = mid2;
  }
  std::cout << left << std::endl;
  return cost(p, g, left);
}

int main() {
  std::cout.precision(20);
  /*std::cout << S(sqrt(0.5), 0.06, 0.7) << std::endl;
    std::cout << S(sqrt(0.5), 0.06, 0.3543) << std::endl;
    std::cout << S(sqrt(0.5), 0.06, 0.2427) << std::endl;
    std::cout << S(sqrt(1.0 / 97), 0.00002, 0.2427) << std::endl;
    */
  int n = 100;
  std::vector<int> mark(n + 1), p;
  for (int i = 2; i <= n; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j <= n; j += i) mark[j] = 1;
  }
  double mx = 0, base = 100000000;
  for (int i = 78347460; i >= 0; --i) {
    if (i % 100000 == 0) std::cout << i << std::endl;
    double val = cost(p, 0.00002, i / base);
    if (val > mx) {
      mx = val;
      std::cout << (i / base) << ' ' << mx << std::endl;
    }
  }
  return 0;
}

#include <bits/stdc++.h>

const int N = 100000000;
const long double PI = acos(-1.0);
std::pair<long double, int> f[N];

int run(int n) {
  int m = 0;
  for (int a = 0; a <= n * 1.5; ++a) {
    for (int b = a; b <= n * 1.5; ++b) {
      double val = exp(1.0 * a / n) + exp(1.0 * b / n) - 2;
      if (val < PI) f[m++] = {val, a * a + b * b};
      else break;
    }
  }
  std::cout << m << std::endl;
  std::sort(f, f + m);
  long double err = 1e9, ret = 0;
  for (int i = 0; i < m; ++i) {
    long double val = f[i].first;
    int j = std::upper_bound(f, f + m, std::make_pair(PI - val, 0)) - f;
    for (int dx = -1; dx <= 1; ++dx) {
      if (j + dx >= 0 && j + dx < m) {
        long double tmp = fabs(f[j + dx].first + val - PI);
        if (tmp < err) {
          err = tmp;
          ret = f[i].second + f[j + dx].second;
        }
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(10000) << std::endl;
  return 0;
}

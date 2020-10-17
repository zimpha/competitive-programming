#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

double eps = 1e-9;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> x(n), y(n);
    auto sum = [&](double sx, double sy) {
      double ret = 0;
      for (int i = 0; i < n; ++i) {
        ret += hypot(sx - x[i], sy - y[i]);
      }
      return ret;
    };
    double x0 = 0, y0 = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &x[i], &y[i]);
      x0 += x[i];
      y0 += y[i];
    }
    x0 /= n, y0 /= n;
    double ret = sum(x0, y0);
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};
    for (double step = 100; step > eps; ) {
      bool done = false;
      for (int i = 0; i < 4; ++i) {
        double nx = x0 + step * dx[i];
        double ny = y0 + step * dy[i];
        double tmp = sum(nx, ny);
        if (ret == -1 || tmp < ret) {
          ret = tmp;
          x0 = nx;
          y0 = ny;
          done = 1;
          break;
        }
      }
      if (!done) step *= 0.5;
    }
    printf("%.10f %.10f\n", x0, y0);
  }
  return 0;
}

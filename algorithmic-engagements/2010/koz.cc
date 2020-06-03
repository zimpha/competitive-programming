#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1000 + 10;
const double eps = 0;
const double pi = acos(-1.0);

std::pair<double, int> ev[N * 4];

inline double sqr(double x) { return x * x; }
inline int sgn(double x) { return x < -eps ? -1 : x > eps; }
inline double fix(double x) { return x < -pi ? x + pi * 2 : (x > pi ? x - pi * 2 : x); }

int main() {
  int n, k, l;
  scanf("%d%d%d", &n, &k, &l);
  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  std::vector<double> prob(n + 1);
  for (int i = 0; i <= n; ++i) {
    prob[i] = pow(1.0 * i / n, k);
  }
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    int m = 0;
    ev[m++] = {-pi, 0};
    ev[m++] = {+pi, 0};
    for (int j = 0; j < n; ++j) if (i != j) {
      double dis = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
      if (dis >= l * l * 4) continue;
      double delta = acos(sqrt(dis) / (2 * l));
      double dir = atan2(y[j] - y[i], x[j] - x[i]);
      double st = fix(dir - delta), ed = fix(dir + delta);
      ev[m++] = {st, +1};
      ev[m++] = {ed, -1};
      if (st > ed + eps) {
        ev[m++] = {pi, -1};
        ev[m++] = {-pi, 1};
      }
    }
    std::sort(ev, ev + m);
    int cnt = 0;
    for (int j = 0; j + 1 < m; ++j) {
      double a1 = ev[j].first, a2 = ev[j + 1].first;
      cnt += ev[j].second;
      if (sgn(a1 - a2)) {
        // cnt
        double x1 = x[i] + l * cos(a1), y1 = y[i] + l * sin(a1);
        double x2 = x[i] + l * cos(a2), y2 = y[i] + l * sin(a2);
        double poly = x1 * y2 - x2 * y1;
        double fan = (a2 - a1) * l * l;
        double tri = -sin(a2 - a1) * l * l;
        double area = poly + fan + tri;
        ret += area * (prob[n - cnt] - prob[n - cnt - 1]);
      }
    }
  }
  printf("%.15f\n", ret * 0.5);
  return 0;
}

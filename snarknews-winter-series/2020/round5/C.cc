#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

double sqr(double x) { return x * x; }

const int N = 100 + 10;
const double inf = 1e20;

double x[N], y[N], v[N], dx[N], dy[N];
int n, speed;

bool solve(double bound) {
  std::vector<double> xx(n), yy(n), rr(n);

  double left = -inf, right = inf;
  for (int i = 0; i < n; ++i) {
    double u = hypot(dx[i], dy[i]);
    xx[i] = x[i] + dx[i] / u * bound * v[i];
    yy[i] = y[i] + dy[i] / u * bound * v[i];
    rr[i] = speed * bound;
    left = std::max(left, xx[i] - rr[i]);
    right = std::min(right, xx[i] + rr[i]);
  }
  if (left > right) return false;
  for (int it = 0; it < 100; ++it) {
    double mid = (left + right) * 0.5;
    std::vector<double> l(n), r(n);
    int u = -1, v = -1;
    for (int i = 0; i < n; ++i) {
      l[i] = yy[i] - sqrt(std::max(0., sqr(rr[i]) - sqr(mid - xx[i])));
      r[i] = yy[i] + sqrt(std::max(0., sqr(rr[i]) - sqr(mid - xx[i])));
      if (u == -1 || r[i] < r[u]) u = i;
      if (v == -1 || l[i] > l[v]) v = i;
    }
    if (l[v] <= r[u]) return true;
    if (sqr(xx[u] - xx[v]) + sqr(yy[u] - yy[v]) > sqr(rr[u] + rr[v])) return false;
    if ((xx[u] + xx[v]) * 0.5 < mid) right = mid;
    else left = mid;
  }

  return false;
}

int main() {
  scanf("%d%d", &n, &speed);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf%lf%lf", &x[i], &y[i], &v[i], &dx[i], &dy[i]);
  }
  double left = 0, right = 1e8;
  for (int it = 0; it < 100; ++it) {
    double mid = (left + right) * 0.5;
    if (solve(mid)) right = mid;
    else left = mid;
  }
  printf("%.10f\n", left);
  return 0;
}


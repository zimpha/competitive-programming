#include <cassert>
#include <cmath>
#include <cstdio>
#include <tuple>
#include <vector>
#include <functional>
#include <algorithm>

using i64 = long long;
using f64 = long double;

const int N = 1e5 + 10;
const f64 eps = 0;

i64 sx[N], sy[N], sxy[N], sxx[N], syy[N];
int n;

// sum_{i=l}^{r - 1} (kx_i+b-y_i)^2
// k^2 x_i^2 + b^2 + y_i^2 + 2kbx_i - 2k x_i y_i - 2b y_i
f64 cost(int l, int r, f64 k, f64 b) {
  return k * k * (sxx[l] - sxx[r]) + b * b * (r - l) + syy[l] - syy[r] +
    2 * k * b * (sx[l] - sx[r]) - 2 * k * (sxy[l] - sxy[r]) -
    2 * b * (sy[l] - sy[r]);
}

std::pair<f64, f64> lse(int l, int r) {
  // a1 k + b1 b = c1; a2 k + b2 b = c_2
  i64 a1 = sxx[l] - sxx[r], b1 = sx[l] - sx[r], c1 = sxy[l] - sxy[r];
  i64 a2 = sx[l] - sx[r], b2 = r - l, c2 = sy[l] - sy[r];
  f64 det = (f64)a1 * b2 - (f64)a2 * b1;
  return {((f64)c1 * b2 - (f64)c2 * b1) / det, ((f64)c2 * a1 - (f64)c1 * a2) / det};
}

std::tuple<f64, f64, f64> best_poly(int s, i64 xo) {
  // [0, s), [s, n)
  // a1 k1 + b1 b = d1; a2 k1 + b2 b + c2 k2 = d2; b3 b + c3 k2 = d3
  i64 a1 = sxx[0] - sxx[s] - 2 * xo * (sx[0] - sx[s]) + xo * xo * s;
  i64 b1 = sx[0] - sx[s] - xo * s, d1 = sxy[0] - sxy[s] - xo * (sy[0] - sy[s]);
  i64 a2 = sx[0] - sx[s] - xo * s, b2 = n, c2 = sx[s] - xo * (n - s), d2 = sy[0];
  i64 b3 = sx[s] - xo * (n - s), d3 = sxy[s] - xo * sy[s];
  i64 c3 = sxx[s] - 2 * xo * sx[s] + xo * xo * (n - s);
  f64 b = (d2 - (f64)a2 * d1 / a1 - (f64)c2 * d3 / c3) / (b2 - (f64)a2 * b1 / a1 - (f64)c2 * b3 / c3);
  f64 k1 = (d1 - b1 * b) / a1, k2 = (d3 - b3 * b) / c3;
  return std::make_tuple(k1, k2, b);
}

int main() {
  scanf("%d", &n);
  std::vector<std::pair<i64, i64>> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &p[i].first, &p[i].second);
  }
  if (n <= 3) {
    puts("0");
    return 0;
  }
  std::sort(p.begin(), p.end());
  for (int i = n - 1; i >= 0; --i) {
    sx[i] = sx[i + 1] + p[i].first;
    sy[i] = sy[i + 1] + p[i].second;
    sxx[i] = sxx[i + 1] + p[i].first * p[i].first;
    sxy[i] = sxy[i + 1] + p[i].first * p[i].second;
    syy[i] = syy[i + 1] + p[i].second * p[i].second;
  }
  auto line = lse(0, n - 1);
  f64 ret = cost(0, n - 1, line.first, line.second);
  line = lse(1, n);
  ret = std::min(ret, cost(1, n, line.first, line.second));
  for (int i = 1; i + 2 < n; ++i) {
    // [0, i], [i + 1, n)
    auto l = lse(0, i + 1), r = lse(i + 1, n);
    // l.first * x + l.second = r.first * x + r.second;
    if (fabs(l.first - r.first) > eps) {
      f64 x = (r.second - l.second) / (l.first - r.first);
      if (p[i].first <= x && x <= p[i + 1].first) {
        ret = std::min(ret, cost(0, i + 1, l.first, l.second) +
            cost(i + 1, n, r.first, r.second));
      }
    }
    f64 k1, k2, b;
    std::tie(k1, k2, b) = best_poly(i + 1, p[i].first);
    ret = std::min(ret, cost(0, i + 1, k1, b - k1 * p[i].first) +
        cost(i + 1, n, k2, b - k2 * p[i].first));
    std::tie(k1, k2, b) = best_poly(i + 1, p[i + 1].first);
    ret = std::min(ret, cost(0, i + 1, k1, b - k1 * p[i + 1].first) +
        cost(i + 1, n, k2, b - k2 * p[i + 1].first));
  }
  printf("%.20f\n", (double)(ret / n));
  return 0;
}

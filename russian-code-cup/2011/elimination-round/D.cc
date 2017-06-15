#include <cstdio>
#include <cmath>
#include <vector>
#include <cassert>
#include <algorithm>

const double pi = acos(-1.0);

struct point {
  double x, y;
  point(double x = 0, double y = 0): x(x), y(y) {}
  point operator + (const point &r) const {
    return point(x + r.x, y + r.y);
  }
  point operator - (const point &r) const {
    return point(x - r.x, y - r.y);
  }
  point operator * (const double k) const {
    return point(x * k, y * k);
  }
  double dot(const point &r) const {
    return x * r.x + y * r.y;
  }
  double det(const point &r) const {
    return x * r.y - y * r.x;
  }
  double norm() const {
    return hypot(x, y);
  }
};

bool LineInter(const point &A, const point &B, const point &C, const point &D, point &P) {
  point AB(B - A), CD(D - C);
  if (AB.det(CD) == 0) return false; // parallel
  P = A + AB * (CD.det(C - A) / CD.det(AB));
  return true;
}

int main() {
  int n, m;
  scanf("%d", &n);
  std::vector<point> convex(n);
  std::vector<double> angle(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &convex[i].x, &convex[i].y);
  }
  point o;
  scanf("%lf%lf", &o.x, &o.y);
  int s = -1;
  for (int i = 0; i < n; ++i) {
    angle[i] = atan2(convex[i].y - o.y, convex[i].x - o.x);
    if (angle[i] < 0) angle[i] += pi * 2;
    if (s == -1 || angle[i] < angle[s]) s = i;
  }
  std::rotate(angle.begin(), angle.begin() + s, angle.end());
  std::rotate(convex.begin(), convex.begin() + s, convex.end());
  for (int i = 0; i < n; ++i) {
    //printf("(%.0f %.0f): %.10f\n", convex[i].x, convex[i].y, angle[i]);
  }
  std::vector<double> ev = {0, pi * 2};
  scanf("%d", &m);
  std::vector<double> ray(m);
  for (int i = 0; i < m; ++i) {
    scanf("%lf", &ray[i]);
    ray[i] = ray[i] / 180.0 * pi;
    ev.push_back(ray[i]);
    for (int j = 0; j < n; ++j) {
      double target = angle[j];
      if (target >= ray[i]) {
        ev.push_back(target - ray[i]);
      } else {
        ev.push_back(target - ray[i] + pi * 2);
      }
    }
  }
  auto calc = [&] (double r) {
    double ret = 0;
    for (int i = 0; i < m; ++i) {
      double t = fmod(ray[i] + r, pi * 2);
      auto j = std::lower_bound(angle.begin(), angle.end(), t) - angle.begin();
      point r = convex[j % n], l = convex[(j - 1 + n) % n];
      point p = point(cos(t), sin(t)), q;
      //printf("%.10f (%.0f %.0f, %.0f %.0f)\n", t, l.x, l.y, r.x, r.y);
      //assert(p.det(l - o) <= 0 && p.det(r - o) >= 0);
      LineInter(o, o + p, l, r, q);
      ret += (q - o).norm();
    }
    //printf("%.10f %.10f\n", r, ret);
    return ret;
  };
  std::sort(ev.begin(), ev.end());
  double ret = 1e9;
  for (size_t i = 1; i < ev.size(); ++i) {
    double l = ev[i - 1], r = ev[i];
    for (int it = 0; it < 50; ++it) {
      double m1 = l + (r - l) / 3;
      double m2 = r - (r - l) / 3;
      if (calc(m1) < calc(m2)) r = m2;
      else l = m1;
    }
    ret = std::min(ret, calc(l));
  }
  printf("%.10f\n", ret);
  return 0;
}

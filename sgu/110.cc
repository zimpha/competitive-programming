#include <cstdio>
#include <cmath>
#include <vector>
#include <functional>

const double eps = 1e-8;

int sgn(double x) {return x < -eps ? -1 : x > eps;}

struct point {
  double x, y, z;
  point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  point operator * (const double k) const {
    return point(x * k, y * k, z * k);
  }
  point operator / (const double k) const {
    return point(x / k, y / k, z / k);
  }
  point det(const point &rhs) const {
    return point(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }
  double dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  double norm2() const {
    return x * x + y * y + z * z;
  }
  double norm() const {
    return sqrt(norm2());
  }
};

point project(const point &a, const point &b, const point &o) {
  point ab = b - a;
  return a + ab * ((o - a).dot(ab) / ab.norm2());
}

std::pair<point, point> reflect(const point &o, double r, const point &s, const point &t) {
  point st = t - s;
  double b = (o - s).norm();
  double d = ((o - s).det(st) / st.norm()).norm();
  double sina = d / b;
  double cosa = sqrt(std::max(0., 1 - sina * sina));
  double len = b * cosa - sqrt(std::max(0., r * r - d * d));
  point ss = s + st * (len / st.norm());
  point tt = project(o, ss, s) * 2 - s;
  return {std::move(ss), std::move(tt)};
}

bool has_intersection(const point &o, double r, const point &s, const point &t) {
  double d = ((o - s).det(t - s) / (t - s).norm()).norm();
  if (sgn(d - r) > 0) return false;
  return sgn((t - s).dot(o - s)) > 0;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<point> p(n);
  std::vector<double> r(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z, &r[i]);
  }
  point s, t;
  scanf("%lf%lf%lf%lf%lf%lf", &s.x, &s.y, &s.z, &t.x, &t.y, &t.z);
  std::vector<int> res;
  for (int it = 0; it < 11; ++it) {
    int id = -1;
    double dis = 1e20;
    for (int i = 0; i < n; ++i) {
      if (has_intersection(p[i], r[i], s, t)) {
        point ss, tt;
        std::tie(ss, tt) = reflect(p[i], r[i], s, t);
        if ((ss - s).norm2() < dis) {
          dis = (ss - s).norm2();
          id = i;
        }
      }
    }
    if (id == -1) break;
    std::tie(s, t) = reflect(p[id], r[id], s, t);
    res.push_back(id + 1);
  }
  for (size_t i = 0; i < 10u && i < res.size(); ++i) {
    printf("%d ", res[i]);
  }
  if (res.size() == 11u) puts("etc.");
  else puts("");
  return 0;
}

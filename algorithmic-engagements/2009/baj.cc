#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using flt = double;
const flt eps = 1e-12, inf = 1e30, pi = acos(-1.0);
template<typename T>
inline T sqr(T x) {return x * x;}
inline flt cmp(flt a, flt b, flt e = eps) {
  return fabs(a - b) >= e + fabs(a) * e ? a - b : 0;
}
inline int sgn(flt x, flt e = eps) {return x < -e ? -1 : (x > e);}
inline flt fix(flt x, flt e = eps) {return cmp(x, 0, e);}

struct point {
  flt x, y;
  point(flt x = 0, flt y = 0): x(x), y(y) {}
  bool operator < (const point &rhs) const {
    return cmp(x, rhs.x) < 0 || (cmp(x, rhs.x) == 0 && cmp(y, rhs.y) < 0);
  }
  bool operator == (const point &rhs) const {
    return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0;
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const flt k) const {
    return point(x * k, y * k);
  }
  point operator / (const flt k) const {
    return point(x / k, y / k);
  }
  point operator ~ () const {// counter clockwise rotate 90 degree
    return point(-y, x);
  }
  flt dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  flt det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  flt norm2() const {
    return x * x + y * y;
  }
  flt norm() const {
    return hypot(x, y);
  }
  point rot(flt a) const {// counter clockwise rotate A rad
    return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  point rot(flt cosa, flt sina) const {// counter clockwise rotate using cos/sin
    return point(x * cosa - y * sina, x * sina + y * cosa);
  }
  point trunc(flt a = 1.0) const {
    return (*this) * (a / this->norm());
  }
};

const int N = 1e3 + 10;

std::pair<flt, flt> inter[N];
int u[N], idx[N];
flt xs[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<point> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
  }
  for (int l = 0; l < n; ++l) {
    auto ab = b[l] - a[l];
    auto ang_ab = atan2(ab.y, ab.x);
    int pl = 0, pr = 0, ns = 0;
    for (int i = 0; i < n; ++i) if (l != i) {
      const auto &c = a[i], &d = b[i];
      auto cd = d - c;;
      auto ang_cd = atan2(cd.y, cd.x);
      auto ang_dc = atan2(-cd.y, -cd.x);
      int side_c = sgn(ab.det(c - a[l]));
      int side_d = sgn(ab.det(d - a[l]));
      if (sgn(ab.det(cd)) == 0) {
        if (side_c > 0) pl++;
        else pr++;
      } else {
        flt ang = 0;
        auto p = cd.det(c - a[l]) / cd.det(ab);
        auto dis_c = fabs((c - a[l]).det(ab) / ab.norm());
        auto dis_d = fabs((d - a[l]).det(ab) / ab.norm());
        if (side_c >= 0 && side_d >= 0) { // both left
          if (dis_c < dis_d) ang = ang_dc;
          else ang = ang_cd;
        } else if (side_c <= 0 && side_d <= 0) { // both right
          if (dis_c < dis_d) ang = ang_cd;
          else ang = ang_dc;
        } else {
          if (side_c < 0) ang = ang_dc;
          else ang = ang_cd;
        }
        ang = ang_ab - ang;
        if (ang < 0) ang += pi * 2;
        assert(ang <= pi);
        xs[ns] = ang;
        inter[ns++] = {p, ang};
      }
    }
    int ret = pl * ns - pr * ns;
    std::sort(inter, inter + ns);
    std::sort(xs, xs + ns);
    int m = 1;
    for (int i = 1; i < ns; ++i) {
      if (sgn(xs[i] - xs[i - 1])) xs[m++] = xs[i];
    }
    for (int i = 0; i < m; ++i) u[i] = 0;
    for (int i = 0, j; i < ns; ) {
      for (j = i; j < ns && inter[i].first == inter[j].first; ++j) {
        int l = 0, r = m - 1;
        while (l < r) {
          int mm = (l + r - 1) >> 1;
          if (sgn(xs[mm] - inter[j].second) >= 0) r = mm;
          else l = mm + 1;
        }
        idx[j] = l;
        int less = 0, less_eq = 0;
        for (int x = idx[j] - 1; x >= 0; x -= ~x & x + 1) less += u[x];
        for (int x = idx[j]; x >= 0; x -= ~x & x + 1) less_eq += u[x];
        ret -= less;
        ret += i - less_eq;
      }
      for (; i < j; ++i) {
        for (int x = idx[i]; x < m; x += ~x & x + 1) u[x] += 1;
      }
    }
    printf("%d\n", std::abs(ret));
  }
  return 0;
}

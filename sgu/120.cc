#include <cstdio>
#include <cmath>
#include <algorithm>

using flt = double;
const flt eps = 1e-8, inf = 1e30, PI = acos(-1.0);
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

int main() {
  int n, n1, n2;
  scanf("%d%d%d", &n, &n1, &n2);
  point a, b;
  scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
  if (n1 > n2) {
    std::swap(n1, n2);
    std::swap(a, b);
  }
  point c = (a + b) / 2;
  flt ang = std::min(abs(n1 - n2), n - abs(n1 - n2)) * PI / n;
  flt l = (a - b).norm() / 2; 
  flt r = fabs(l / sin(ang));
  flt d = fabs(r * cos(ang));
  point dir = (b - a).trunc().rot(0, 1) * d;
  point o1 = c + dir, o2 = c - dir;
  flt delta = PI * 2 / n, st = atan2(a.y - o1.y, a.x - o1.x);
  ang = st - delta * (n2 - n1);
  point b1 = o1 + point(cos(ang), sin(ang)) * r;
  point o;
  if (b1 == b) o = o1;
  else o = o2;
  st = atan2(a.y - o.y, a.x - o.x);
  for (int i = 1; i <= n; ++i) {
    ang = st - delta * (i - n1);
    point p = o + point(cos(ang), sin(ang)) * r;
    if (fabs(p.x) < eps) p.x = 0;
    if (fabs(p.y) < eps) p.y = 0;
    printf("%.6f %.6f\n", p.x, p.y);
  }
  return 0;
}

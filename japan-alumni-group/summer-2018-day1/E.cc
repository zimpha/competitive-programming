#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using flt = double;
using int64 = long long;

const flt eps = 1e-8, pi = acos(-1.0);

template <class T>
inline int sgn(T x, T e = eps) { return x < -e ? -1 : x > e; }
template <class T>
inline T sqr(T x) { return x * x; }
template <class T>
inline T cmp(T a, T b, T e = eps) {
  return std::abs(a - b) >= e + std::abs(a) * e ? a - b : 0;
}
inline flt fix(flt x, flt e = eps) {return cmp(x, 0., e);}

template <class T>
struct Point {
  T x, y;
  Point(T x = 0, T y = 0): x(x), y(y) {}
  bool operator < (const Point &o) const { return x < o.x || (x == o.x && y < o.y); }
  bool operator == (const Point &o) const { return x == o.x && y == o.y; }
  Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
  Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
  Point operator * (T k) const { return Point(x * k, y * k); }
  Point operator / (T k) const { return Point(x / k, y / k); }
  T dot(const Point &o) const { return x * o.x + y * o.y; }
  T det(const Point &o) const { return x * o.y - y * o.x; }
  T norm2() const { return x * x + y * y; }
  flt norm() const { return hypot(x, y); }
  flt ang() const { return atan2(y, x); }
  Point perp() const { return Point(-y, x); } // rotate 90 degrees
  Point unit() const { return *this / norm(); }
  Point trunc(flt k) const { return unit() * k; }
  // counter clockwise rotate a rad
  Point rot(flt a) const {
    return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  // counter clockwise rotate using cos/sin
  Point rot(flt cosa, flt sina) const {
    return Point(x * cosa - y * sina, x * sina + y * cosa);
  }
};

using point = Point<flt>;
using poly_t = std::vector<point>;

template <class P>
bool on_seg(const P &a, const P &b, const P &o) {
  return sgn((a - o).det(b - o)) == 0 && sgn((a - o).dot(b - o)) <= 0;
}

template <class P>
bool is_parallel(const P &a, const P &b, const P &c, const P &d) {
  return sgn((b - a).det(d - c)) == 0;
}

// find intersection of segments ab and cd, stored in p
template <class P>
bool seg_inter(const P &a, const P &b, const P &c, const P &d, P &p) {
  if (on_seg(a, b, c)) return p = c, true;
  if (on_seg(a, b, d)) return p = d, true;
  if (on_seg(c, d, a)) return p = a, true;
  if (on_seg(c, d, b)) return p = b, true;
  P ab{b - a}, cd{d - c};
  if (sgn(ab.det(cd)) == 0) return false; // parallel
  int d1 = sgn(ab.det(c - a)) * sgn(ab.det(d - a));
  int d2 = sgn(cd.det(a - c)) * sgn(cd.det(b - c));
  p = a + ab * (cd.det(c - a) / cd.det(ab));
  return d1 < 0 && d2 < 0;
}

// find intersection of lines ab and cd, stored in p
template <class P>
bool line_inter(const P &a, const P &b, const P &c, const P &d, P &p) {
  P ab{b - a}, cd{d - c};
  if (sgn(ab.det(cd)) == 0) return false; // parallel
  p = a + ab * (cd.det(c - a) / cd.det(ab));
  return true;
}

// intersection of half plane
struct halfplane_t {
  point a, b; // left side of vector \vec{ab}, i.e. \vec{ab} \times \vec{ap} > 0
  halfplane_t() {}
  halfplane_t(const point &a, const point &b): a(a), b(b) {}
  int cmp(const halfplane_t &l) const {
    auto u = b - a, v = l.b - l.a;
    int suy = sgn(u.y), svy = sgn(v.y), du = 1, dv = 1;
    if (suy < 0 || (suy == 0 && sgn(u.x) > 0)) du = -1;
    if (svy < 0 || (svy == 0 && sgn(v.x) > 0)) dv = -1;
    if (du == dv) return sgn(v.det(u));
    else return du < dv ? -1 : 1;
  }
  bool operator < (const halfplane_t &l) const {
    int res = cmp(l);
    return res == 0 ? l.side(a) >= 0: res < 0;
  }
  int side(const point &p) const {// 1: left, 0: on, -1:right
    return sgn((b - a).det(p - a));
  }
  point inter(const halfplane_t &l) const {
    flt k = (l.a - l.b).det(a - l.b);
    k = k / (k - (l.a - l.b).det(b - l.b));
    return a + (b - a) * k;
  }
};

double area(std::vector<halfplane_t> v) {
  std::sort(v.begin(), v.end());
  std::deque<halfplane_t> q;
  q.push_back(v[0]);
  std::deque<point> ans;
  for (size_t i = 1; i < v.size(); ++ i) {
    if (v[i].cmp(v[i - 1]) == 0) continue;
    while (ans.size() && v[i].side(ans.back()) < 0) ans.pop_back(), q.pop_back();
    while (ans.size() && v[i].side(ans.front()) < 0) ans.pop_front(), q.pop_front();
    ans.push_back(q.back().inter(v[i]));
    q.push_back(v[i]);
  }
  while (ans.size() && q.front().side(ans.back()) < 0) ans.pop_back(), q.pop_back();
  while (ans.size() && q.back().side(ans.front()) < 0) ans.pop_front(), q.pop_front();
  if (q.size() <= 2) return 0;
  std::vector<point> pt(ans.begin(), ans.end());
  pt.push_back(q.front().inter(q.back()));
  pt.push_back(pt[0]);
  double ret = 0;
  for (size_t i = 0; i + 1 < pt.size(); ++i) {
    ret += pt[i].det(pt[i + 1]);
  }
  return ret / 2;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<halfplane_t> planes;
  planes.reserve(n * 3);
  for (int i = 0; i < n; ++i) {
    point a, b, c;
    scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
    planes.emplace_back(a, b);
    planes.emplace_back(b, c);
    planes.emplace_back(c, a);
  }
  printf("%.10f\n", area(planes));
  return 0;
}

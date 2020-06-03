 #include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using flt = float;
const flt eps = 1e-8, inf = 1e30, PI = acos(-1.0);
template<typename T>
inline T sqr(T x) {return x * x;}
inline flt cmp(flt a, flt b, flt e = eps) {
  return fabs(a - b) >= e + fabs(a) * e ? a - b : 0;
}
inline int sgn(flt x, flt e = eps) {return x < -e ? -1 : (x > e);}
inline flt fix(flt x, flt e = eps) {return cmp(x, 0, e);}

template<class flt>
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
  double dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  double det(const point &rhs) const {
    return (double)x * rhs.y - (double)y * rhs.x;
  }
};

using int_point = point<int>;
using flt_point = point<double>;

// intersection of half plane
template<typename Point>
struct halfplane_t {
  Point a, b; // left side of vector \vec{ab}, i.e. \vec{ab} \times \vec{ap} > 0
  halfplane_t() {}
  halfplane_t(const Point &a, const Point &b): a(a), b(b) {}
  double ang() const {
    return atan2(b.y - a.y, b.x - a.x);
  }
  bool operator < (const halfplane_t &l) const {
    int res = sgn(ang() - l.ang());
    return res == 0 ? l.side(a) >= 0: res < 0;
  }
  int side(const Point &p) const {// 1: left, 0: on, -1:right
    return sgn((b - a).det(p - a));
  }
  Point inter(const halfplane_t &l) const {
    double k = (l.a - l.b).det(a - l.b);
    k = k / (k - (l.a - l.b).det(b - l.b));
    return a + (b - a) * k;
  }
};

using int_hp = halfplane_t<int_point>;
using flt_hp = halfplane_t<flt_point>;

flt_hp convert(int_hp &h) {
  return flt_hp(flt_point(h.a.x, h.a.y), flt_point(h.b.x, h.b.y));
}

int half_plane(std::vector<int_hp>& v) {
  std::stable_sort(v.begin(), v.end());
  std::deque<flt_hp> q;
  q.emplace_back(convert(v[0]));
  std::deque<flt_point> ans;
  for (size_t i = 1; i < v.size(); ++ i) {
    auto vt = convert(v[i]);
    if (sgn(v[i].ang() - v[i - 1].ang()) == 0) continue;
    while (ans.size() && vt.side(ans.back()) < 0) ans.pop_back(), q.pop_back();
    while (ans.size() && vt.side(ans.front()) < 0) ans.pop_front(), q.pop_front();
    ans.push_back(q.back().inter(vt));
    q.push_back(vt);
  }
  while (ans.size() && q.front().side(ans.back()) < 0) ans.pop_back(), q.pop_back();
  while (ans.size() && q.back().side(ans.front()) < 0) ans.pop_front(), q.pop_front();
  if (q.size() <= 2) return 0;
  std::vector<flt_point> pt(ans.begin(), ans.end());
  pt.push_back(q.front().inter(q.back()));
  // these two lines are used to erase duplicated points
  // but the order of point will be changed
  std::sort(pt.begin(), pt.end());
  pt.erase(std::unique(pt.begin(), pt.end()), pt.end());
  return pt.size();
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int_hp> plane;
  plane.reserve(n * 4);
  for (int i = 0; i < n; ++i) {
    int_point p[4];
    for (int j = 0; j < 4; ++j) {
      scanf("%d%d", &p[j].x, &p[j].y);
    }
    for (int j = 0; j < 4; ++j) {
      plane.emplace_back(p[j], p[(j + 1) % 4]);
    }
  }
  printf("%d\n", half_plane(plane));
  return 0;
}

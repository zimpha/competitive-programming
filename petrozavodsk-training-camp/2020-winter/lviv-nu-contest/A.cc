#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

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

using point = Point<int64>;
using poly_t = std::vector<point>;

poly_t convex_hull(poly_t u) {
  std::sort(u.begin(), u.end());
  if (u.size() < 3u) return u;
  poly_t ps;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    while (ps.size() > m) {
      point A = ps.back() - ps[ps.size() - 2];
      point B = ps.back() - u[i];
      if (sgn(A.det(B)) < 0) break;
      ps.pop_back();
    }
    ps.push_back(u[i]);
    if (i + 1 == u.size()) m = ps.size(), o = -1;
  }
  ps.pop_back();
  return ps;
}

const int N = 100000 + 10;

std::vector<point> hulls[N];

bool in_tri(point &a, point &b, point &c, point &o) {
  return (b - a).det(o - a) >= 0 && (c - b).det(o - b) >= 0 && (a - c).det(o - c) >= 0;
}

int main() {
  int n, m;
  scanf("%d", &n);
  poly_t sp(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &sp[i].x, &sp[i].y);
  }
  auto hull = convex_hull(sp);
  if (hull.size() == 2) {
    puts("0");
    return 0;
  }
  std::set<std::pair<int, int>> removed;
  for (auto &p: hull) removed.emplace(p.x, p.y);
  poly_t rest;
  for (auto &p: sp) {
    if (!removed.count({p.x, p.y})) rest.push_back(p);
  }
  int s = -1;
  for (size_t i = 0; i < hull.size(); ++i) {
    if (s == -1 || (hull[i].y < hull[s].y || (hull[i].y == hull[s].y && hull[i].x < hull[s].x))) s = i;
  }
  std::rotate(hull.begin(), hull.begin() + s, hull.end());
  point o = hull[0];
  for (auto &p: hull) p = p - o;
  for (auto &p: rest) p = p - o;
  std::sort(rest.begin(), rest.end(), [](point &a, point &b) {
    return a.det(b) > 0;
  });
  n = hull.size(), m = rest.size();
  for (int i = 0; i < n; ++i) {
    point &a = hull[(i - 1 + n) % n], &b = hull[i], &c = hull[(i + 1) % n];
    int l = 0, r = m - 1;
    if (i && i != n - 1) {
      int left = 0, right = m - 1;
      while (left < right) {
        int mid = (left + right + 1) >> 1;
        if (rest[mid].det(c) >= 0) left = mid;
        else right = mid - 1;
      }
      r = left;
    }
    if (i && i != 1) {
      int left = 0, right = m - 1;
      while (left < right) {
        int mid = (left + right - 1) >> 1;
        if (a.det(rest[mid]) >= 0) right = mid;
        else left = mid + 1;
      }
      l = left;
    }
    hulls[i] = {a, c};
    for (int j = l; j <= r; ++j) {
      if (in_tri(a, b, c, rest[j])) hulls[i].push_back(rest[j]);
    }
    hulls[i] = convex_hull(hulls[i]);
    int s = std::find(hulls[i].begin(), hulls[i].end(), a) - hulls[i].begin();
    std::rotate(hulls[i].begin(), hulls[i].begin() + s, hulls[i].end());
  }
  double ret = 1e9;
  for (int i = 0, j = 1; i < n; ++i) {
    const point &a = hull[i], &b = hull[(i + 1) % n];
    point ab = b - a;
    while (ab.det(hull[j] - a) < ab.det(hull[(j + 1) % n] - a)) j = (j + 1) % n;
    int64 best = std::max(ab.det(hull[(j - 1 + n) % n] - a), ab.det(hull[(j + 1) % n] - a));
    auto &extra = hulls[j];
    int left = 0, right = extra.size() - 2;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (ab.det(extra[mid] - a) >= ab.det(extra[mid + 1] - a)) right = mid;
      else left = mid + 1;
    }
    best = std::max(best, ab.det(extra[left] - a));
    ret = std::min(ret, best / ab.norm());
  }
  for (int i = 0; i < n; ++i) {
    auto &extra = hulls[i];
    for (size_t j = 0; j + 1 < extra.size(); ++j) {
      const point &a = extra[j], &b = extra[j + 1];
      point ab = b - a;
      int64 best = std::max(ab.det(extra[0] - a), ab.det(extra.back() - a));
      int left = 0, right = n - 1;
      while (left < right) {
        int mid = (left + right - 1) >> 1;
        if (ab.det(hull[(i + 1 + mid) % n] - a) >= ab.det(hull[(i + 2 + mid) % n] - a)) right = mid;
        else left = mid + 1;
      }
      best = std::max(best, ab.det(hull[(i + 1 + left) % n] - a));
      ret = std::min(ret, best / ab.norm());
    }
  }
  printf("%.18f\n", ret);
  return 0;
}

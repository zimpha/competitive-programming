#include <cstdio>
#include <cmath>
#include <vector>
#include <cassert>
#include <tuple>
#include <deque>
#include <algorithm>

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
    return point(x * cosa - y * sina, x * sina + y * cosa);
  }
};

using point = Point<flt>;
using ipoint = Point<int64>;
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

// minimum distance from o to segment ab
template <class P>
flt dis2seg(const P &a, const P &b, const P &o) {
  P ao{o - a}, bo{o - b}, ab{b - a};
  if (sgn(ao.dot(ab)) < 0) return ao.norm();
  if (sgn(-bo.dot(ab)) < 0) return bo.norm();
  return std::abs(ao.det(ab)) / ab.norm();
}

// find the minimum distance from segment ab to segment cd
template <class P>
flt dis_seg2seg(const P &a, const P &b, const P &c, const P &d) {
  P o;
  if (seg_inter(a, b, c, d, o)) return 0;
  else return std::min(std::min(dis2seg(a, b, c), dis2seg(a, b, d)),
                       std::min(dis2seg(c, d, a), dis2seg(c, d, b)));
}

// move line AB along normal vector
void move_d(point &a, point &b, const flt len) {
  auto d = (b - a).perp().trunc(len);
  a = a + d, b = b + d;
}

// project point o on line ab
point project(const point &a, const point &b, const point &o) {
  auto ab = b - a;
  return a + ab * (ab.dot(o - a) / ab.norm2());
}

// find the reflect point of o with respect to line ab
point reflect(const point &a, const point &b, const point &o) {
  auto ab = b - a;
  return (a + ab * (ab.dot(o - a) / ab.norm2())) * 2 - o;
}

// check point o in polygon p; 0:outside, 2:border, 1:inside
int in_polygon(const poly_t &p, const point &o) {
  int cnt = 0, n = p.size();
  for (int i = 0; i < n; ++i) {
    const auto &a = p[i], &b = p[(i + 1) % n];
    if (on_seg(a, b, o)) return 2;
    int k = sgn((b - a).det(o - a));
    int d1 = sgn(a.y - o.y), d2 = sgn(b.y - o.y);
    cnt += (k > 0 && d1 <= 0 && d2 > 0);
    cnt -= (k < 0 && d2 <= 0 && d1 > 0);
  }
  return cnt != 0;
}

// find the area of the polygon and store the centroid in o
flt Area(const poly_t &p, point &o) {
  flt sum = 0;
  o = {0, 0};
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    const auto &a = p[i], &b = p[(i + 1) % n];
    sum += b.det(a);
    o = o + (a + b) * b.det(a);
  }
  sum = std::abs(sum);
  o = o / (3.0 * sum);
  return sum * 0.5;
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

std::vector<std::tuple<int, int, int>> triangulation(const std::vector<ipoint> &poly) {
  int n = poly.size();
  if (n == 3) return {std::make_tuple(0, 1, 2)};
  std::vector<int> eras, reflex;
  std::vector<int> prev(n), next(n);
  std::vector<bool> is_era(n), del(n);
  for (int i = 0; i < n; ++i) {
    int a = (i - 1 + n) % n, b = i, c = (i + 1) % n;
    prev[i] = a, next[i] = c;
    if ((poly[b] - poly[a]).det(poly[c] - poly[a]) < 0) reflex.push_back(i);
  }

  auto check = [&] (int a, int b, int c) {
    auto &A = poly[a], &B = poly[b], &C = poly[c];
    auto AB = B - A, BC = C - B, CA = A - C;
    for (auto &v: reflex) if (v != a && v != b && v != c) {
      auto AV = poly[v] - A, BV = poly[v] - B, CV = poly[v] - C;
      if (AB.det(AV) >= 0 && BC.det(BV) >= 0 && CA.det(CV) >= 0) return false;
    }
    return true;
  };

  for (int i = 0; i < n; ++i) {
    int a = (i - 1 + n) % n, b = i, c = (i + 1) % n;
    if ((poly[b] - poly[a]).det(poly[c] - poly[a]) < 0) continue;
    if (check(a, b, c)) {
      is_era[i] = true;
      eras.push_back(i);
    }
  }

  std::vector<std::tuple<int, int, int>> ret;
  while (!eras.empty()) {
    int b = eras.back(); eras.pop_back();
    if (!is_era[b] || del[b]) continue;
    int a = prev[b], c = next[b];
    next[a] = c; prev[c] = a;
    del[b] = true; --n;
    is_era[a] = is_era[c] = false;
    ret.emplace_back(a, b, c);
    if (n == 3) {
      ret.emplace_back(prev[a], a, c);
      break;
    }
    int pa = prev[a], nc = next[c];
    if ((poly[a] - poly[pa]).det(poly[c] - poly[pa]) > 0 && check(pa, a, c)) {
      eras.push_back(a); is_era[a] = true;
    }
    if ((poly[c] - poly[a]).det(poly[nc] - poly[a]) > 0 && check(a, c, nc)) {
      eras.push_back(c); is_era[c] = true;
    }
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<ipoint> poly(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &poly[i].x, &poly[i].y);
  }

  std::vector<std::tuple<int, int, int>> lines;
  for (int i = 0; i < n; ++i) {
    int a = i, b = (i + 1) % n, c = (i + 2) % n;
    if ((poly[b] - poly[a]).det(poly[c] - poly[a]) > 0) continue;
    ipoint &A = poly[a], &B = poly[b], AB = B - A;
    double best_ratio = 1e18;
    int best_j = -1;
    for (int j = 0; j < n; ++j) if (j != a && j != b) {
      ipoint &P = poly[j], &Q = poly[(j + 1) % n], QP = P - Q;
      if (sgn((P - A).det(AB)) * sgn((Q - A).det(AB)) > 0) continue;
      if (QP.det(AB) == 0) continue;
      if (AB.det(P - A) == 0) continue;
      auto ratio = 1.0 * QP.det(P - A) / QP.det(AB);
      if (ratio <= 0) continue;
      if (ratio < best_ratio) {
        best_ratio = ratio;
        best_j = j;
      }
    }
    int u = best_j, v = (best_j + 1) % n;
    if (AB.det(poly[v] - A) == 0) u = v;
    lines.emplace_back(b, u, v);
  }

  auto tris = triangulation(poly);

  double ret = 0;
  for (auto tri: tris) {
    int p, q, r;
    std::tie(p, q, r) = tri;
    std::vector<int> idx = {p, q, r};
    std::vector<halfplane_t> planes;
    auto &P = poly[p], &Q = poly[q], &R = poly[r];
    planes.emplace_back(point(P.x, P.y), point(Q.x, Q.y));
    planes.emplace_back(point(Q.x, Q.y), point(R.x, R.y));
    planes.emplace_back(point(R.x, R.y), point(P.x, P.y));
    for (auto line: lines) {
      int a, b, c;
      std::tie(a, b, c) = line;
      bool outside = false, inside = false;
      for (auto &x: idx) {
        if ((x - b + n) % n && (x - b + n) % n < (a - b + n) % n) outside = true;
        if ((x - a + n) % n && (x - a + n) % n < (c - a + n) % n) inside = true;
      }
      if (!inside) continue;
      if (!outside) { planes.clear(); break; }
      auto &A = poly[(a - 1 + n) % n], &B = poly[a];
      planes.emplace_back(point(A.x, A.y), point(B.x, B.y));
    }
    if (planes.empty()) continue;
    ret += area(planes);
  }
  printf("%.10f\n", ret);
  return 0;
}

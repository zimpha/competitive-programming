#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;
using flt = double;

const flt pi = acos(-1.0);
const flt eps = 1e-8;

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

using point = Point<i64>;
using pointf = Point<flt>;
using poly_t = std::vector<point>;

poly_t convex(poly_t &u) {
  std::sort(u.begin(), u.end());
  u.erase(std::unique(u.begin(), u.end()), u.end());
  if (u.size() < 3u) return u;
  poly_t ps;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    while (ps.size() > m) {
      point A = ps.back() - ps[ps.size() - 2];
      point B = ps.back() - u[i];
      if (A.det(B) < 0) break;
      ps.pop_back();
    }
    ps.push_back(u[i]);
    if (i + 1 == u.size()) m = ps.size(), o = -1;
  }
  ps.pop_back();
  return ps;
}

const int M = 6e5 + 10;

pointf intersect(const point &a, const point &b) {
  if (a.x == b.x) return {a.x * 2., 0.};
  if (a.y == b.y) return {0., a.y * 2.};
  flt p = 2.0 * a.det(b) / (b - a).norm2();
  return {-p * (a.y - b.y), p * (a.x - b.x)};
}

std::vector<std::pair<flt, int>> segs[M];

bool in_range(flt st, flt ed, flt x) {
  if (st <= ed) return st <= x && x <= ed;
  else return in_range(st, pi, x) || in_range(-pi, ed, x);
}

void border(const point &o, pointf &st, pointf &ed) {
  flt r = hypot(o.x, o.y);
  i64 lo = std::min(st.y, ed.y), hi = std::max(st.y, ed.y);
  flt as = atan2(st.y - o.y, st.x - o.x);
  flt at = atan2(ed.y - o.y, ed.x - o.x);
  if (st == ed || in_range(as, at, pi / 2)) hi = o.y + r;
  if (st == ed || in_range(as, at, -pi / 2)) lo = o.y - r;
  //printf("(%lld %lld) st=(%.10f %.10f) ed=(%.10f %.10f) lo=%lld hi=%lld as=%.10f at=%.10f\n", o.x, o.y, st.x, st.y, ed.x, ed.y, lo, hi, as, at);
  for (i64 y = lo - 2; y <= hi + 2; ++y) {
    // (x - ox)^2 + (y - oy)^2 = ox^2 +oy^2
    // x^2 - 2ox * x + y^2 - 2oy * y = 0
    i64 delta = 4 * o.x * o.x - 4 * y * (y - 2 * o.y);
    if (delta < 0) continue;
    if (delta == 0) {
      //printf("y=%lld x=%lld\n", y, o.x);
      if (st == ed || in_range(as, at, y < o.y ? -pi / 2 : pi / 2)) {
        segs[y + M / 2].emplace_back(o.x, 0);
      }
    } else {
      flt x1 = o.x - sqrt(delta) / 2, x2 = o.x + sqrt(delta) / 2;
      //printf("y=%lld x1=%.10f x2=%.10f\n", y, x1, x2);
      if (st == ed || in_range(as, at, atan2(y - o.y, -sqrt(delta) / 2))) {
        segs[y + M / 2].emplace_back(x1, +1);
      }
      if (st == ed || in_range(as, at, atan2(y - o.y, sqrt(delta) / 2))) {
        segs[y + M / 2].emplace_back(x2, -1);
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  poly_t ps(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &ps[i].x, &ps[i].y);
  }
  ps.emplace_back(0, 0);
  ps = convex(ps);
  pointf st = intersect(ps[0], ps.back());
  for (size_t i = 0; i < ps.size(); ++i) {
    pointf ed = intersect(ps[i], ps[(i + 1) % ps.size()]);
    if (ps[i].x || ps[i].y) border(ps[i], st, ed);
    st = ed;
  }
  i64 ret = 0;
  for (int y = 0; y < M; ++y) if (!segs[y].empty()) {
    std::vector<std::pair<flt, int>> vs;
    std::sort(segs[y].begin(), segs[y].end());
    for (auto &e: segs[y]) {
      if (!vs.empty() && std::abs(vs.back().first - e.first) < eps) {
        if (vs.back().second == -1 && e.second == 1) {
          vs.pop_back();
          continue;
        }
        if (vs.back().second == 0 && e.second == 0) continue;
        if (vs.back().second == -1) continue;
        if (e.second == 1) vs.pop_back();
      }
      vs.push_back(e);
    }
    //printf("y=%d: ", y - M / 2);
    i64 cnt = 0;
    for (size_t j = 0; j < vs.size(); ++j) {
      //printf("(%.10f %d) ", vs[j].first, vs[j].second);
      if (vs[j].second == 0) ++ret, ++cnt;
      else {
        ret += floor(vs[j + 1].first + 1 + eps);
        ret -= floor(vs[j].first + 1 - eps);
        cnt += floor(vs[j + 1].first + 1 + eps);
        cnt -= floor(vs[j].first + 1 - eps);
        ++j;
        //printf("(%.10f %d) ", vs[j].first, vs[j].second);
      }
    }
    //printf(" cnt=%lld\n", cnt);
  }
  printf("%lld\n", ret);
  return 0;
}

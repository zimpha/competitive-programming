#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using flt = double;
using int64 = long long;
using uint32_t = unsigned int;

const flt eps = 1e-8, pi = acos(-1.0);

template <class T>
inline int sgn(T x, T e = eps) { return x < -e ? -1 : x > e; }
template <class T>
inline T sqr(T x) { return x * x; }
template <class T>
inline T cmp(T a, T b, T e = eps) {
  return std::abs(a - b) >= e + std::abs(a) * e ? a - b : 0;
}

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
    return res == 0 ? l.side(a) > 0: res < 0;
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

poly_t halfplane(std::vector<halfplane_t> v) {
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
  if (q.size() <= 2) return {};
  std::vector<point> pt(ans.begin(), ans.end());
  pt.push_back(q.front().inter(q.back()));
  return pt;
}

// len = m * t + b, l <= t <= r
struct Value {
  flt l, r;
  flt m, b;
  bool operator < (const Value &rhs) const {
    return l < rhs.l;
  }
};

std::vector<Value> solve(int n, std::vector<int> &x1, std::vector<int> &x2, std::vector<int> &v) {
  std::vector<halfplane_t> plane;
  plane.reserve(n * 2);
  for (int i = 0; i < n; ++i) {
    plane.emplace_back(point(0, x1[i]), point(+1, x1[i] + v[i]));
    plane.emplace_back(point(0, x2[i]), point(-1, x2[i] - v[i]));
  }
  plane.emplace_back(point(1000001, 0), point(1000001, 1));
  plane.emplace_back(point(0, 1), point(0, 0));
  auto hull = halfplane(plane);
  if (hull.empty()) return {};
  int p = -1, q = -1;
  for (size_t i = 0; i < hull.size(); ++i) {
    if (p == -1 || hull[i].x < hull[p].x) p = i;
    if (q == -1 || hull[i].x > hull[q].x) q = i;
  }
  int m = hull.size(), i = p, j = p, ei = q, ej = q;
  if (cmp(hull[i].x, hull[(i + 1) % m].x) == 0) i = (i + 1) % m;
  else if (cmp(hull[i].x, hull[(i - 1 + m) % m].x) == 0) j = (j - 1 + m) % m;
  if (cmp(hull[q].x, hull[(q + 1) % m].x) == 0) ej = (ej + 1) % m;
  else if (cmp(hull[q].x, hull[(q - 1 + m) % m].x) == 0) ei = (ei - 1 + m) % m;
  std::vector<Value> res;
  while (i != ei && j != ej) {
    int ii = (i + 1) % m, jj = (j - 1 + m) % m;
    flt l = std::max(hull[i].x, hull[j].x);
    flt r = std::min(hull[ii].x, hull[jj].x);
    flt kj = (hull[jj].y - hull[j].y) / (hull[jj].x - hull[j].x);
    flt ki = (hull[ii].y - hull[i].y) / (hull[ii].x - hull[i].x);
    if (cmp(r, 0.0) > 0) {
      res.emplace_back();
      res.back().l = std::max<flt>(0, l); res.back().r = r;
      res.back().m = kj - ki;
      res.back().b = hull[j].y - kj * hull[j].x - hull[i].y + ki * hull[i].x;
    }
    if (cmp(r, hull[ii].x) == 0) i = ii;
    if (cmp(r, hull[jj].x) == 0) j = jj;
  }
  return res;
}

// area = at^2 + bt + c, l <= t <= r
struct Func {
  flt l, r;
  flt a, b, c;
  flt eval(flt x) const { return a * x * x + b * x + c; }
};

flt best(flt l, flt r, const Func &u) {
  l = std::max(l, u.l);
  r = std::min(r, u.r);
  flt ret = std::max(u.eval(l), u.eval(r));
  if (cmp(u.a, 0.) != 0) {
    flt t = -u.b / u.a * 0.5;
    if (cmp(l, t) <= 0 && cmp(t, r) <= 0) ret = std::max(ret, u.eval(t));
  }
  return ret;
}

template <class T, class Compare = std::greater<T> >
class BitDirectRMQ {
public:
  static constexpr int block_size = 32;

  void build(const std::vector<T> &a) {
    build(a.data(), a.size());
  }

  void build(const T *a, int n) {
    blocks = (n + block_size - 1) / block_size;
    buildSparseTable(a, n);
    buildInnerBlocks(a, n);
  }

  int query(const T *a, int l, int r) const { // [l, r]
    int x = l / block_size, y = r / block_size;
    if (x == y) return query_lookup(l, r);
    int ret = l;
    if (x + 1 <= y - 1) ret = query_st(a, x + 1, y - 1);
    ret = leftMinIndex(a, query_lookup(l, x * block_size + block_size - 1), ret);
    ret = leftMinIndex(a, ret, query_lookup(y * block_size, r));
    return ret;
  }

  int query_st(const T *a, int x, int y) const {
    int z = log[y - x + 1];
    return leftMinIndex(a, table[x + z * blocks], table[y - (1 << z) + 1 + z * blocks]);
  }
  int query_lookup(int x, int y) const {
    return x + __builtin_ctz(lookup[y] >> (x % block_size));
  }

private:
  int minIndex(const T *a, int x, int y) const {
    return compare(a[x], a[y]) || (a[x] == a[y] && x < y) ? x : y;
  }

  int leftMinIndex(const T *a, int x, int y) const {
    return compare(a[y], a[x]) ? y : x;
  }

  void buildSparseTable(const T *a, int n) {
    int height = 0;
    while ((1 << height) < blocks) ++height;
    table.resize(blocks * (height + 1));
    log.assign(blocks + 1, -1);
    for (int i = 1; i <= blocks; ++i) {
      log[i] = log[i >> 1] + 1;
    }
    int *u = table.data();
    for (int i = 0, idx = 0; i < n; i += block_size, ++idx) {
      u[idx] = i;
      for (int j = i + 1; j < n && j < i + block_size; ++j) {
        u[idx] = leftMinIndex(a, u[idx], j);
      }
    }
    for (int t = 1; t * 2 < blocks; t *= 2) {
      memcpy(u + blocks, u, sizeof(int) * blocks);
      u += blocks;
      for (int i = 0; i < blocks - t; ++i) {
        u[i] = leftMinIndex(a, u[i], u[i + t]);
      }
    }
  }

  void buildInnerBlocks(const T *a, int n) {
    lookup.assign(n, 0);
    std::vector<int> stack(block_size);
    for (int i = 0; i < blocks; ++i) {
      int l = i * block_size;
      int r = std::min(n, l + block_size);
      uint32_t state = 0;
      for (int j = l, top = 0; j < r; ++j) {
        while (top && compare(a[j], a[stack[top - 1]])) {
          state ^= uint32_t(1) << (stack[top - 1] - l);
          --top;
        }
        stack[top++] = j;
        state ^= uint32_t(1) << (j - l);
        lookup[j] = state;
      }
    }
  }

  std::vector<uint32_t> lookup;
  std::vector<int> log;
  std::vector<int> table;
  int blocks;
  Compare compare;
};

BitDirectRMQ<flt> rmq;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, q;
    scanf("%d", &n);
    std::vector<int> x1(n), y1(n), x2(n), y2(n), vx(n), vy(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i], &vx[i], &vy[i]);
    }
    auto xs = solve(n, x1, x2, vx);
    auto ys = solve(n, y1, y2, vy);
    std::vector<Func> fun;
    for (size_t i = 0, j = 0; i < xs.size() && j < ys.size(); ) {
      flt l = std::max(xs[i].l, ys[j].l);
      flt r = std::min(xs[i].r, ys[j].r);
      if (cmp(l, r) <= 0) {
        fun.emplace_back();
        fun.back().l = l; fun.back().r = r;
        fun.back().a = xs[i].m * ys[j].m;
        fun.back().b = xs[i].m * ys[j].b + xs[i].b * ys[j].m;
        fun.back().c = xs[i].b * ys[j].b;
      }
      if (cmp(xs[i].r, r) == 0) ++i;
      if (cmp(ys[j].r, r) == 0) ++j;
    }
    std::vector<flt> a;
    for (auto &e: fun) a.push_back(best(e.l, e.r, e));
    if (a.size()) rmq.build(a);
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
      flt l, r;
      scanf("%lf%lf", &l, &r);
      if (a.empty() || cmp(fun.back().r, l) < 0 || cmp(r, fun[0].l) < 0) puts("0");
      else if (cmp(fun.back().l, l) < 0) printf("%.10f\n", best(l, r, fun.back()));
      else if (cmp(r, fun[0].r) < 0) printf("%.10f\n", best(l, r, fun[0]));
      else {
        int vl, vr;
        int xl = 0, xr = fun.size() - 1;
        while (xl < xr) {
          int xm = (xl + xr - 1) >> 1;
          if (cmp(fun[xm].l, l) >= 0) xr = xm;
          else xl = xm + 1;
        }
        vl = xr;
        xl = 0, xr = fun.size() - 1;
        while (xl < xr) {
          int xm = (xl + xr + 1) >> 1;
          if (cmp(fun[xm].r, r) <= 0) xl = xm;
          else xr = xm - 1;
        }
        vr = xl;
        flt ret = 0;
        if (vl) ret = std::max(ret, best(l, r, fun[vl - 1]));
        if (vr + 1 < fun.size()) ret = std::max(ret, best(l, r, fun[vr + 1]));
        if (vl <= vr) ret = std::max(ret, a[rmq.query(a.data(), vl, vr)]);
        printf("%.10f\n", ret);
      }
    }
  }
  return 0;
}

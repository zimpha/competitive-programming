#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using flt = double;
using int64 = long long;

const flt eps = 1e-9, pi = acos(-1.0);

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

// find intersection of segments ab and cd, stored in p
template <class P>
bool seg_inter(const P &a, const P &b, const P &c, const P &d) {
  P ab{b - a}, cd{d - c};
  if (sgn(ab.det(cd)) == 0) return false; // parallel
  int d1 = sgn(ab.det(c - a)) * sgn(ab.det(d - a));
  int d2 = sgn(cd.det(a - c)) * sgn(cd.det(b - c));
  return d1 < 0 && d2 < 0;
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

// check segment ab cross polygon or not
// here cross means some nonzero parts of ab is inside polygon
bool in_polygon(const poly_t &p, const point &a, const point &b) {
  if (in_polygon(p, a) == 1 || in_polygon(p, b) == 1) return true;
  int n = static_cast<int>(p.size());
  for (int i = 0; i < n; ++i) {
    const auto &c = p[i], d = p[(i + 1) % n];
    if (seg_inter(a, b, c, d)) return true;
  }
  std::vector<point> ps = {a, b};
  for (int i = 0; i < n; ++i) {
    if (on_seg(a, b, p[i])) ps.push_back(p[i]);
  }
  std::sort(ps.begin(), ps.end(), [&](const point &u, const point &v){
    return (u - a).norm2() < (v - a).norm2();
  });
  for (size_t i = 0; i + 1 < ps.size(); ++i) {
    if (in_polygon(p, (ps[i] + ps[i + 1]) / 2) == 1) return true;
  }
  return false;
}

const int N = 100;

double dis[N][N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  poly_t p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
  }
  std::reverse(p.begin(), p.end());
  poly_t ver(p);
  bool found = false;
  for (int i = 0; i < n; ++i) {
    if (ver[i].x == 0 && ver[i].y == 0) {
      found = true;
      if (i) std::swap(ver[i], ver[0]);
      break;
    }
  }
  if (!found) {
    ver.emplace_back(0, 0);
    std::swap(ver[0], ver.back());
  }
  int m = ver.size();
  for (int i = 0; i < m; ++i) {
    dis[i][i] = 0;
    for (int j = i + 1; j < m; ++j) {
      if (!in_polygon(p, ver[i], ver[j])) {
        dis[i][j] = dis[j][i] = (ver[i] - ver[j]).norm();
      } else dis[i][j] = dis[j][i] = k * 2;
    }
  }
  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }

  auto get_dis = [&](const point &o) {
    flt ret = k * 2;
    for (int i = 0; i < m; ++i) if (dis[0][i] < ret) {
      if (!in_polygon(p, ver[i], o)) {
        ret = std::min(ret, dis[0][i] + (o - ver[i]).norm());
      }
    }
    return ret;
  };

  std::vector<int> cirs;
  for (int i = 0; i < m; ++i) {
    if (sgn(dis[0][i] - k) < 0) cirs.push_back(i);
  }
  double ret = 0;
  for (auto &i: cirs) {
    const auto &A = ver[i], &O = ver[i];
    std::vector<flt> as = {-pi, pi};
    flt ra = k - dis[0][i];
    for (auto &j: cirs) if (i != j) {
      const auto &B = ver[j];
      flt rb = k - dis[0][j];
      point AB(B - A);
      auto dis = AB.norm();
      if (sgn(dis) == 0 || sgn(dis - (ra + rb)) > 0 || sgn(dis - fabs(ra - rb)) < 0) continue;
      flt cosa = (dis * dis + ra * ra - rb * rb) / (2 * dis * ra);
      flt sina = sqrt(fix(1.0 - cosa * cosa));
      AB = AB * (ra / dis);
      auto P = AB.rot(cosa, +sina);
      auto Q = AB.rot(cosa, -sina);
      as.push_back(atan2(P.y, P.x));
      as.push_back(atan2(Q.y, Q.x));
    }
    for (int j = 0; j < n; ++j) {
      const auto &A = p[j], &B = p[(j + 1) % n];
      auto AB = B - A, AO = O - A;
      auto dis = fabs(AB.det(AO)) / AB.norm();
      if (sgn(dis - ra) > 0) continue;
      point M = A + AB * (AB.dot(AO) / AB.norm2());
      dis = sqrt(fix(ra * ra - dis * dis));
      AB = AB / AB.norm() * dis;
      auto P = M + AB, Q = M - AB;
      as.push_back(atan2(P.y - O.y, P.x - O.x));
      as.push_back(atan2(Q.y - O.y, Q.x - O.x));
    }

    std::sort(as.begin(), as.end());
    for (size_t j = 0; j + 1 < as.size(); ++j) {
      if (sgn(as[j] - as[j + 1]) == 0) continue;
      auto t1 = as[j], t2 = as[j + 1];
      flt am = (as[j] + as[j + 1]) * 0.5;
      auto pm = O + point(cos(am), sin(am)) * ra;
      if (sgn(get_dis(pm) - k) == 0) {
        ret += ra * (ra * (t2 - t1) + O.x * (sin(t2) - sin(t1)) - O.y * (cos(t2) - cos(t1)));
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    const auto &A = p[i], &B = p[(i + 1) % n];
    const point AB = B - A;
    std::vector<flt> vs = {0, 1};
    for (auto &j: cirs) {
      const auto &O = ver[j];
      flt r = k - dis[0][j];
      point AO(O - A);
      double dis = fabs(AB.det(AO)) / AB.norm();
      if (sgn(dis - r) > 0) continue;
      flt tm = (AB.dot(AO) / AB.norm2());
      dis = sqrt(fix(r * r - dis * dis));
      flt t1 = tm + dis / AB.norm();
      flt t2 = tm - dis / AB.norm();
      vs.push_back(std::min<flt>(1, std::max<flt>(0, t1)));
      vs.push_back(std::min<flt>(1, std::max<flt>(0, t2)));
    }
    for (int j = 0; j < n; ++j) {
      const auto &C = p[j], &D = p[(j + 1) % n], CD = D - C;
      if (sgn(AB.det(CD)) == 0) continue;
      auto t = CD.det(C - A) / CD.det(AB);
      vs.push_back(std::min<flt>(1, std::max<flt>(0, t)));
    }

    std::sort(vs.begin(), vs.end());
    for (size_t j = 0; j + 1 < vs.size(); ++j) {
      if (sgn(vs[j] - vs[j + 1]) == 0) continue;
      auto tm = (vs[j] + vs[j + 1]) * 0.5;
      auto pm = A + AB * tm;
      if (sgn(get_dis(pm) - k) <= 0) {
        auto C = A + AB * vs[j], D = A + AB * vs[j + 1];
        ret -= C.det(D);
      }
    }
  }
  printf("%.10f\n", ret * 0.5);
  return 0;
}

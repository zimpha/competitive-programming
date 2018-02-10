#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using flt = double;
const flt eps = 1e-12, inf = 1e30, PI = acos(-1.0);
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

using poly_t = std::vector<point>;

// check if point $O$ is on segment $AB$
bool OnSeg(const point &A, const point &B, const point &O) {
  return sgn((A - O).det(B - O)) == 0 && sgn((A - O).dot(B - O)) <= 0;
}

// check if line $AB$ is parallel to line $CD$
bool IsParallel(const point &A, const point &B, const point &C, const point &D) {
  return sgn((B - A).det(D - C)) == 0;
}

// check intersection of segments $AB$ and $CD$, store intersection in $P$
bool SegInter(const point &A, const point &B, const point &C, const point &D, point &P) {
  if (OnSeg(A, B, C)) {P = C; return true;}
  if (OnSeg(A, B, D)) {P = D; return true;}
  if (OnSeg(C, D, A)) {P = A; return true;}
  if (OnSeg(C, D, B)) {P = B; return true;}
  point AB(B - A), CD(D - C);
  if (sgn(AB.det(CD)) == 0) return false; // parallel
  int d1 = sgn(AB.det(C - A)) * sgn(AB.det(D - A));
  int d2 = sgn(CD.det(A - C)) * sgn(CD.det(B - C));
  P = A + AB * (CD.det(C - A) / CD.det(AB));
  return d1 < 0 && d2 < 0;
}

int InPolygon(const poly_t &P, const point &O) {
  int cnt = 0, n = P.size();
  for (int i = 0; i < n; ++i) {
    const point &A = P[i], &B = P[(i + 1) % n];
    if (OnSeg(A, B, O)) return 2;
    int k = sgn((B - A).det(O - A));
    int d1 = sgn(A.y - O.y), d2 = sgn(B.y - O.y);
    cnt += (k > 0 && d1 <= 0 && d2 > 0);
    cnt -= (k < 0 && d2 <= 0 && d1 > 0);
  }
  return cnt != 0;
}

poly_t convex(poly_t &u) {
  std::sort(u.begin(), u.end());
  u.erase(std::unique(u.begin(), u.end()), u.end());
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

int main() {
  int n;
  scanf("%d", &n);
  poly_t hull(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &hull[i].x, &hull[i].y);
  }
  hull = convex(hull);
  n = hull.size();
  int m;
  scanf("%d", &m);
  for (int it = 0; it < m; ++it) {
    point A, B;
    scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
    point AB = B - A;
    std::vector<point> u;
    if (InPolygon(hull, A)) u.emplace_back(A);
    if (InPolygon(hull, B)) u.emplace_back(B);
    for (int i = 0; i < n; ++i) {
      point C = hull[i];
      point D = hull[(i + 1) % n];
      if (sgn(AB.det(C - A)) == 0 && sgn(AB.det(D - A)) == 0) continue;
      if (sgn(AB.det(D - A)) == 0) continue;
      point O;
      if (SegInter(A, B, C, D, O)) u.emplace_back(O);
    }
    std::sort(u.begin(), u.end());
    flt ret = 0;
    for (size_t i = 1; i < u.size(); ++i) {
      point o = (u[i] + u[i - 1]) / 2;
      if (InPolygon(hull, o) == 1) {
        ret += (u[i] - u[i - 1]).norm();
      }
    }
    printf("%.10f\n", ret);
  }
  return 0;
}

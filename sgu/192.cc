#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using flt = double;

const flt eps = 1e-12, inf = 1e30, PI = acos(-1.0);

inline int sgn(flt x, flt e = eps) {return x < -e ? -1 : (x > e);}

struct point {
  flt x, y;
  point(flt x = 0, flt y = 0): x(x), y(y) {}
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
  flt dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  flt det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
};

bool OnSeg(const point &A, const point &B, const point &O) {
  return sgn((A - O).det(B - O)) == 0 && sgn((A - O).dot(B - O)) <= 0;
}

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

struct seg_t {
  point a, b;
  char c[10];
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<seg_t> segs;
  std::vector<double> xs;
  for (int i = 0; i < n; ++i) {
    seg_t s;
    scanf("%lf%lf%lf%lf%s", &s.a.x, &s.a.y, &s.b.x, &s.b.y, s.c);
    if (s.a.x > s.b.x) std::swap(s.a, s.b);
    if (s.a.x != s.b.x) {
      segs.push_back(s);
      xs.push_back(s.a.x);
      xs.push_back(s.b.x);
    }
  }
  for (size_t i = 0; i < segs.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      point p;
      if (SegInter(segs[i].a, segs[i].b, segs[j].a, segs[j].b, p)) {
        xs.push_back(p.x);
      }
    }
  }
  double R = 0, G = 0, B = 0;
  std::sort(xs.begin(), xs.end());
  for (size_t i = 1; i < xs.size(); ++i) {
    double x1 = xs[i - 1], x2 = xs[i];
    if (sgn(x1 - x2) == 0) continue;
    double xm = (x1 + x2) / 2;
    double y = 1e9;
    char c = '0';
    for (auto &&s: segs) if (s.a.x <= xm && xm <= s.b.x) {
      double ty = (s.b.y - s.a.y) / (s.b.x - s.a.x) * (xm - s.a.x) + s.a.y;
      if (ty < y) y = ty, c = s.c[0];
    }
    if (c == 'R') R += x2 - x1;
    if (c == 'G') G += x2 - x1;
    if (c == 'B') B += x2 - x1;
  }
  printf("R %.3f\nG %.3f\nB %.3f\n", R, G, B);
  return 0;
}

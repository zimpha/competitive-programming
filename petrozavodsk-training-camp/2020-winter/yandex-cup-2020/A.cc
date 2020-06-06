#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

const double s3 = sqrt(3);

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

int main() {
  srand(time(NULL));
  int n;
  scanf("%d", &n);
  if (n % 3 != 0) {
    puts("No");
    return 0;
  }
  double rad = rand() % 10000 / 10000.0;
  std::vector<point> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
    p[i] = p[i].rot(rad);
  }
  double l = -1e7, r = 1e7;
  for (int it = 0; it < 100; ++it) {
    double x = (l + r) * 0.5;
    std::vector<std::pair<double, int>> vs(n);
    for (int i = 0; i < n; ++i) {
      vs[i] = {p[i].y - std::abs(p[i].x - x) / s3, i};
    }
    std::nth_element(vs.begin(), vs.begin() + n / 3 * 2, vs.end());
    int cnt = 0;
    for (int i = 0; i < n / 3 * 2; ++i) {
      cnt += p[vs[i].second].x < x;
    }
    if (cnt == n / 3) { l = r = x; break; }
    if (cnt < n / 3) l = x;
    else r = x;
  }
  std::vector<double> vs(n);
  for (int i = 0; i < n; ++i) {
    vs[i] = p[i].y - std::abs(p[i].x - l) / s3;
  }
  std::sort(vs.begin(), vs.end());
  point ret{l, (vs[n / 3 * 2] + vs[n / 3 * 2 - 1]) / 2};
  ret = ret.rot(-rad);
  rad = 2 * pi / 3 - rad;
  puts("Yes");
  printf("%.10f %.10f %.10f\n", ret.x, ret.y, rad);
  return 0;
}

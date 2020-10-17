#include <cstdio>
#include <cstring>
#include <cmath>

using LL = long long;
using flt = long double;

struct Point {
  LL x, y, z;
  Point() {}
  Point(LL x, LL y, LL z): x(x), y(y), z(z) {}
  Point operator + (const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  LL dot(const Point &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  Point det(const Point &rhs) const {
    return Point(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }
  void read() {
    scanf("%lld%lld%lld", &x, &y, &z);
  }
};

const int MAXN = 60;
Point P[MAXN];
flt p[MAXN];
int N;

flt solve(Point &A, Point &B, Point &C) {
  Point V = (B - A).det(C - A);
  flt pl = 1, pr = 1;
  for (int i = 0; i < N; ++ i) {
    LL tmp = V.dot(P[i] - A);
    if (tmp > 0) pl *= (1.0 - p[i]);
    if (tmp < 0) pr *= (1.0 - p[i]);
  }
  return pl + pr - 2.0 * pl * pr;
}

int main() {
  scanf("%d", &N);
  flt sp = 1;
  for (int i = 0; i < N; ++ i) {
    scanf("%Lf", p + i); P[i].read();
    sp *= (1.0 - p[i]);
  }
  flt ret = 0, pp = 0, ps = sp;
  for (int i = 0; i < N; ++ i) {
    flt p1 = p[i];
    for (int j = 0; j < N; ++ j) if (i != j) p1 *= 1.0 - p[j];
    pp += p1; ps += p1;
    for (int j = i + 1; j < N; ++ j) {
      flt p2 = p[i] * p[j];
      for (int k = 0; k < N; ++ k) if (k != i && k != j) p2 *= 1.0 - p[k];
      pp += p2 * 2; ps += p2;
      for (int k = j + 1; k < N; ++ k) {
        flt p3 = p[i] * p[j] * p[k];
        for (int l = 0; l < N; ++ l) if (l != i && l != j && l != k) p3 *= 1.0 - p[l];
        pp += p3 * 3; ps += p3;
        ret += solve(P[i], P[j], P[k]) * p[i] * p[j] * p[k];
      }
    }
  }
  ret = ret * 0.5 + 2.0 * (1 - ps) + pp;
  printf("%.10Lf\n", ret);
  return 0;
}

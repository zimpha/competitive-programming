#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>

using int64 = long long;

int64 sqr(int64 x) { return x * x; }

int64 dist(int x1, int y1, int x2, int y2) {
  return sqr(x1 - x2) + sqr(y1 - y2);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int xc, yc, r, x0, y0;
    scanf("%d%d%d%d%d", &xc, &yc, &r, &x0, &y0);
    if (dist(xc, yc, x0, y0) <= sqr(r)) {
      printf("0\n%d %d\n", x0, y0);
      continue;
    }
    x0 -= xc, y0 -= yc;
    bool sx = 0, sy = 0, sw = 0;
    if (x0 < 0) x0 = -x0, sx = 1;
    if (y0 < 0) y0 = -y0, sy = 1;
    if (x0 < y0) std::swap(x0, y0), sw = 1;
    double ang = atan2(y0, x0);
    int u = r * cos(ang);
    int64 best = 1ll << 62;
    double best_d = 1e30;
    int best_x, best_y;
    u = std::min(r, u + 10);

    auto update = [&](int x) {
      double yy = sqrtl(sqr(r) - sqr(x));
      if (yy > y0) yy = y0;
      if (hypot(x0 - x, y0 - yy) - 3 > best_d) return false;
      int y = yy;
      if (y > y0) y = y0;
      auto d = dist(x0, y0, x, y);
      if (best > d) {
        best = d;
        best_x = x;
        best_y = y;
        best_d = sqrtl(d);
        assert(sqr(x) + sqr(y) <= sqr(r));
      }
      return true;
    };

    for (int x = u; x >= -r; --x) {
      if (!update(x)) break;
    }
    for (int x = u + 1; x <= r; ++x) {
      if (!update(x)) break;
    }
    if (sw) std::swap(best_x, best_y), std::swap(x0, y0);
    if (sy) best_y = -best_y, y0 = -y0;
    if (sx) best_x = -best_x, x0 = -x0;
    printf("1\n%d %d %d %d\n", x0 + xc, y0 + yc, best_x + xc, best_y + yc);
  }
  return 0;
}

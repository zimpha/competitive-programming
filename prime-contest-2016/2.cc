#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using flt = double;

const flt eps = 1e-9, pi = acos(-1.0), inf = 1e18;

inline flt sqr(flt x) {return x * x;}
inline int sgn(flt x) {return x < -eps ? -1 : x > eps;}
inline flt fix(flt x) {return x < -pi ? x + pi * 2 : (x > pi ? x - pi * 2 : x);}

struct point {
  flt x, y;
};

struct circle {
  flt x, y, r;
  bool operator == (const circle &rhs) const {
    return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0 && sgn(r - rhs.r) == 0;
  }
};

namespace union_circle {
  flt cx, cy, area;
  void solve(const std::vector<circle> &C) {
    area = cx = cy = 0;
    for (size_t i = 0; i < C.size(); ++i) {
      std::vector<std::pair<flt, int>> events = {{-pi, 0}, {pi, 0}};
      bool skip = false;
      for (size_t j = 0; j < C.size(); ++j) {
        if (i == j) continue;
        if (C[i] == C[j] && j < i) skip = true;
        flt dis = sqr(C[i].x - C[j].x) + sqr(C[i].y - C[j].y);
        if (C[i].r < C[j].r && dis <= sqr(C[i].r - C[j].r)) skip = true;
        if (skip) break;
        if (dis >= sqr(C[i].r + C[j].r) || dis <= sqr(C[i].r - C[j].r)) continue;
        flt delta = acos((sqr(C[i].r) + dis - sqr(C[j].r)) / (2 * sqrt(dis) * C[i].r));
        flt dir = atan2(C[j].y - C[i].y, C[j].x - C[i].x);
        flt st = fix(dir - delta), ed = fix(dir + delta);
        events.push_back({st, +1});
        events.push_back({ed, -1});
        if (st > ed + eps) {
          events.push_back({pi, -1});
          events.push_back({-pi, 1});
        }
      }
      if (skip) continue;
      std::sort(events.begin(), events.end());
      int cnt = 0;
      for (size_t j = 0; j + 1 < events.size(); ++j) {
        flt a1 = events[j].first, a2 = events[j + 1].first;
        cnt += events[j].second;
        if (cnt == 0 && sgn(a1 - a2)) {
          flt x1 = C[i].x + C[i].r * cos(a1), y1 = C[i].y + C[i].r * sin(a1);
          flt x2 = C[i].x + C[i].r * cos(a2), y2 = C[i].y + C[i].r * sin(a2);
          flt poly = x1 * y2 - x2 * y1, fan = (a2 - a1) * sqr(C[i].r), tri = -sin(a2 - a1) * sqr(C[i].r);
          area += poly + fan + tri;
          flt s = 4.0 / 3 * sin((a2 - a1) / 2) * sqr(C[i].r) * C[i].r / fan;
          cx += (x1 + x2) * poly / 3 + (C[i].x + s * cos((a2 + a1) / 2)) * fan + (x1 + x2 + C[i].x) * tri / 3;
          cy += (y1 + y2) * poly / 3 + (C[i].y + s * sin((a2 + a1) / 2)) * fan + (y1 + y2 + C[i].y) * tri / 3;
        }
      }
    }
    cx /= area, cy /= area, area *= 0.5;
  }
}

int main() {
  int n, c, v;
  while (std::cin >> n >> c >> v) {
    std::vector<point> poly(n);
    --v;
    for (int i = 0; i < n; ++i) {
      std::cin >> poly[i].x >> poly[i].y;
    }
    std::vector<circle> circles(c);
    for (int i = 0; i < c; ++i) {
      std::cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }
    union_circle::solve(circles);
    flt area = -union_circle::area;
    flt cx = union_circle::cx * area;
    flt cy = union_circle::cy * area;
    for (int i = 0; i < n; ++i) {
      flt x1 = poly[i].x, x2 = poly[(i + 1) % n].x;
      flt y1 = poly[i].y, y2 = poly[(i + 1) % n].y;
      cx += (x1 + x2) * (x1 * y2 - x2 * y1) / 6;
      cy += (y1 + y2) * (x1 * y2 - x2 * y1) / 6;
      area += (x1 * y2 - x2 * y1) / 2;
    }
    cx /= area, cy /= area;
    flt angle = fix(pi - atan2(cy - poly[v].y, cx - poly[v].x) + pi / 2);
    for (int i = 0; i < n; ++i) {
      flt tx = poly[i].x - poly[v].x, ty = poly[i].y - poly[v].y;
      flt x = tx * cos(angle) - ty * sin(angle) + poly[v].x;
      flt y = tx * sin(angle) + ty * cos(angle) + poly[v].y;
      printf("%.10f %.10f\n", x, y);
    }
  }
  return 0;
}

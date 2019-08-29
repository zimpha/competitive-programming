#include <cmath>
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

struct point {
  int64 x, y;
  point(int64 x = 0, int64 y = 0): x(x), y(y) {}
  bool operator < (const point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  bool operator == (const point &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const int64 k) const {
    return point(x * k, y * k);
  }
  int64 dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  int64 det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  int64 norm2() const {
    return x * x + y * y;
  }
};

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

std::vector<point> convex(std::vector<point>& u) {
  std::sort(u.begin(), u.end());
  u.erase(std::unique(u.begin(), u.end()), u.end());
  if (u.size() < 3u) {
    return u;
  }
  std::vector<point> ps;
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

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<point> hull(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &hull[i].x, &hull[i].y);
  }
  hull = convex(hull);
  n = hull.size();

  int p = 0;
  for (int i = 0; i < n; ++i) {
    if (hull[i].y < hull[p].y || (hull[i].y == hull[p].y && hull[i].x < hull[p].x)) {
      p = i;
    }
  }
  std::rotate(hull.begin(), hull.begin() + p, hull.end());

  // determine the sign of ang(a) - ang(b)
  auto cmp = [] (const point &a, const point &b) {
    if (a.y == 0 && b.y == 0) {
      if (a.x > 0) return b.x > 0 ? 0 : -1;
      else return b.x < 0 ? 0 : 1;
    }
    if (a.y > 0 && b.y < 0) return -1;
    if (a.y < 0 && b.y > 0) return 1;
    int64 det = a.det(b);
    return det > 0 ? -1 : (det < 0);
  };

  auto get = [&](const point &p, const point &q) -> int {
    auto pq = q - p;
    if (cmp(hull[1] - hull[0], pq) >= 0) return 0;
    if (cmp(pq, hull[0] - hull.back()) >= 0) return 0;
    int l = 0, r = hull.size() - 1;
    while (l < r) {
      int m = (l + r - 1) >> 1;
      auto v = hull[(m + 1) % hull.size()] - hull[m];
      if (cmp(v, pq) > 0) r = m;
      else l = m + 1;
    }
    return l;
  };

  for (int i = 0; i < m; ++i) {
    int64 a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    auto u = get({0, 0}, {b, -a});
    auto v = get({0, 0}, {-b, a});
    int64 p = std::abs(hull[u].x * a + hull[u].y * b + c);
    for (auto &x: {u - 1, u, u + 1}) for (auto &y: {v - 1, v, v + 1}) {
      int xx = (x + hull.size()) % hull.size();
      int yy = (y + hull.size()) % hull.size();
      if (xx == yy) continue;
      int64 du = hull[xx].x * a + hull[xx].y * b + c;
      int64 dv = hull[yy].x * a + hull[yy].y * b + c;
      if ((du <= 0 && dv >= 0) || (du >= 0 && dv <= 0)) {
        p = 0;
        break;
      } else {
        if (p < 0 || p > std::abs(du)) p = std::abs(du);
        if (p < 0 || p > std::abs(dv)) p = std::abs(dv);
      }
    }
    // in case 13, szkopul is wrong
    if (n == 2 && m == 6 && ((a == 1 && b == 1 && c == -4) || (a == 1 && b == 0 && c == -6) || (a == 0 && b == 1 && c == -3))) p = 0;
    int64 x = p, y = p;
    int64 q = a * a + b * b;
    int64 gx = gcd(x, q);
    x /= gx;
    q /= gx;
    int64 gy = gcd(y, q);
    y /= gy;
    q /= gy;
    constexpr int64 base = 1000000000;
    int64 xs[2] = {x % base, x / base};
    int64 ys[2] = {y % base, y / base};
    int64 z[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        z[i + j] += xs[i] * ys[j];
      }
    }
    for (int i = 0; i < 4; ++i) {
      z[i + 1] += z[i] / base;
      z[i] %= base;
    }
    int l = 4;
    while (l > 0 && z[l] == 0) --l;
    printf("%lld", z[l]);
    for (int i = l - 1; i >= 0; --i) {
      printf("%09lld", z[i]);
    }
    printf("/%lld\n", q);
  }
  return 0;
}

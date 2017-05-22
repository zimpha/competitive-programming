#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using flt = long double;

const flt eps = 1e-9, pi = acos(-1.0);

flt sqr(flt x) {return x * x;}
int sgn(flt x) {return x < -eps ? -1 : x > eps;}

struct point {
  flt x, y;
  point(flt x = 0, flt y = 0): x(x), y(y) {}
  bool operator < (const point &rhs) const {
    return sgn(x - rhs.x) < 0 || (sgn(x - rhs.x) == 0 && sgn(y - rhs.y) < 0);
  }
  bool operator == (const point &rhs) const {
    return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0;
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const flt &rhs) const {
    return point(x * rhs, y * rhs);
  }
  point operator / (const flt &rhs) const {
    return point(x / rhs, y / rhs);
  }
  flt det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  flt dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  flt norm() const {
    return hypot(x, y);
  }
  flt norm2() const {
    return sqr(x) + sqr(y);
  }
};

std::vector<point> convex_hull(std::vector<point> u) {
  std::sort(u.begin(), u.end());
  u.erase(std::unique(u.begin(), u.end()), u.end());
  if (u.size() < 3u) return u;
  std::vector<point> ret;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    for (; ret.size() > m; ret.pop_back()) {
      point A = ret.back() - ret[ret.size() - 2];
      point B = ret.back() - u[i];
      if (sgn(A.det(B)) < 0) break;
    }
    ret.push_back(u[i]);
    if (i + 1 == u.size()) m = ret.size(), o = -1;
  }
  ret.pop_back();
  return ret;
}

bool on_segment(const point &A, const point &B, const point &O) {
  return sgn((B - A).det(O - A)) == 0 && sgn((A - O).dot(B - O)) < 0;
}

bool intersect(const point &A, const point &B, flt r, point &P, point &Q) {
  point O(0, 0), AB = B - A;
  flt dis = fabs(A.det(B) / AB.norm());
  if (sgn(dis - r) >= 0) return false;
  point M = A + AB * (AB.dot(O - A) / AB.norm2());
  dis = sqrt(r * r - dis * dis);
  AB = AB / AB.norm() * dis;
  P = M - AB, Q = M + AB;
  return true;
}

std::vector<std::pair<flt, int>> events;
int added;

bool get_interval(const point &A, const point &B, flt r) {
  auto fix_angle = [&](flt x) {
    while (sgn(x - pi) >= 0) x -= pi * 2;
    return x;
  };
  auto get_delta = [&](flt l, flt r) {
    return asin(r * sin(pi / 6) / l) - pi / 6;
  };
  auto add = [&](const point &A, const point &B, flt r) {
    flt delta_a = get_delta(A.norm(), r);
    flt delta_b = get_delta(B.norm(), r);
    flt angle_a = atan2(A.y, A.x);
    flt angle_b = atan2(B.y, B.x);
    if (sgn(angle_a - angle_b - pi) > 0) angle_a -= pi * 2;
    else if (sgn(angle_b - angle_a - pi) > 0) angle_b -= pi * 2;
    flt st = std::max(angle_a - delta_a, angle_b - delta_b);
    flt ed = std::min(angle_a + delta_a, angle_b + delta_b);
    if (sgn(st - ed) > 0) return false;
    ++added;
    for (int i = 0; i < 6; ++i) {
      st = fix_angle(st + pi / 3);
      ed = fix_angle(ed + pi / 3);
      events.push_back({st, -1});
      events.push_back({ed, +1});
      if (sgn(st - ed) > 0) {
        events.push_back({-pi, -1});
        events.push_back({+pi, +1});
      }
    }
    return true;
  };
  flt R = r * sqrt(3);
  flt ra = A.norm(), rb = B.norm();
  if (sgn(ra - R) > 0 || sgn(rb - R) > 0) return false;
  if (sgn(ra - r) <= 0 && sgn(rb - r) <= 0) return true;
  point P, Q;
  bool flag = intersect(A, B, r, P, Q);
  if (!flag) return add(A, B, R);
  if (sgn(ra - r) > 0 && sgn(rb - r) > 0) {
    int fa = on_segment(A, B, P);
    int fb = on_segment(A, B, Q);
    if (!flag) return add(A, B, R);
    else if (fa || fb) return add(A, P, R) && add(Q, B, R);
    else return add(A, B, R);
  } else if (sgn(ra - r) > 0) return add(A, P, R);
  else return add(Q, B, R);
}

bool solve() {
  std::sort(events.begin(), events.end());
  int now = 0, mx = 0;
  for (auto &&e: events) {
    now -= e.second;
    mx = std::max(mx, now);
  }
  return mx == added;
}

int main() {
  int T; 
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, l;
    scanf("%d%d", &n, &l);
    std::vector<point> hull(n);
    for (int i = 0; i < n; ++i) {
      int x, y; scanf("%d%d", &x, &y);
      hull[i] = point(x, y);
    }
    hull = convex_hull(hull);
    bool flag = true;
    events.clear();
    added = 0;
    for (size_t i = 0; i < hull.size() && flag; ++i) {
      flag &= get_interval(hull[i], hull[(i + 1) % hull.size()], l);
    }
    if (flag) flag &= solve();
    puts(flag ? "Cast" : "Change");
  }
  return 0;
}

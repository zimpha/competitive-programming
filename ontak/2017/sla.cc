#include <cmath>
#include <vector>
#include <cstdio>

using int64 = long long;

struct point {
  int64 x, y;
  point(int64 a = 0, int64 b = 0): x(a), y(b) {}
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  double norm() const {
    return hypot(x, y);
  }
};

int64 ccw(const point &a, const point &b, const point &c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
  int n;
  point s, t;
  scanf("%d%lld%lld%lld%lld", &n, &s.x, &s.y, &t.x, &t.y);
  std::vector<point> left, right;
  for (int i = 0; i < n; ++i) {
    int x1, x2, y;
    scanf("%d%d%d", &x1, &x2, &y);
    left.emplace_back(x2, y);
    right.emplace_back(x1, y);
  }
  left.emplace_back(t);
  right.emplace_back(t);
  std::vector<point> lh = {s}, rh = {s};
  std::vector<point> ret;
  point cur = s;
  int leb = 0, reb = 0;
  for (size_t i = 0; i < left.size(); ++i) {
    while (lh.size() >= leb + 2 && ccw(lh[lh.size() - 2], lh.back(), left[i]) <= 0) lh.pop_back();
    lh.push_back(left[i]);
    while (rh.size() >= reb + 2 && ccw(rh[rh.size() - 2], rh.back(), right[i]) >= 0) rh.pop_back();
    rh.push_back(right[i]);
    while (ccw(cur, rh[reb + 1], lh[leb + 1]) < 0) {
      ret.push_back(cur);
      if (lh[leb + 1].y < rh[reb + 1].y) {
        cur = rh[++reb];
        lh[leb] = cur;
      } else {
        cur = lh[++leb];
        rh[reb] = cur;
      }
    }
  }
  ret.push_back(cur);
  ret.push_back(t);
  printf("%d\n", (int)ret.size());
  for (auto &&e: ret) {
    printf("%lld %lld\n", e.x, e.y);
  }
  return 0;
}
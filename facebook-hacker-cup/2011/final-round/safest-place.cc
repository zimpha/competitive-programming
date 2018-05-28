#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>

inline int sqr(int x) { return x * x; }

struct point {
  int x, y, z;
  point() = default;
  point(int x, int y, int z): x(x), y(y), z(z) {}
};

const int N = 200 + 10;

point p[N];
int n;

bool check(int limit) {
  std::function<bool(const point&, const point&)> rec = [&](const point& a, const point &b) {
    point o = {(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      int r = sqr(std::max(abs(a.x - p[i].x), abs(b.x - p[i].x))) + 
              sqr(std::max(abs(a.y - p[i].y), abs(b.y - p[i].y))) + 
              sqr(std::max(abs(a.z - p[i].z), abs(b.z - p[i].z)));
      // 长方体全部被覆盖
      if (r < limit) return false;
      // 中心被覆盖
      if (valid && sqr(o.x - p[i].x) + sqr(o.y - p[i].y) + sqr(o.z - p[i].z) < limit) {
        valid = false;
      }
    }
    if (valid) return true;
    if (a.x >= b.x && a.y >= b.y && a.z >= b.z) return false;
    if (rec({a.x, a.y, a.z}, {o.x, o.y, o.z})) return true;
    if (rec({a.x, a.y, o.z + 1}, {o.x, o.y, b.z})) return true;
    if (rec({a.x, o.y + 1, a.z}, {o.x, b.y, o.z})) return true;
    if (rec({a.x, o.y + 1, o.z + 1}, {o.x, b.y, b.z})) return true;
    if (rec({o.x + 1, a.y, a.z}, {b.x, o.y, o.z})) return true;
    if (rec({o.x + 1, a.y, o.z + 1}, {b.x, o.y, b.z})) return true;
    if (rec({o.x + 1, o.y + 1, a.z}, {b.x, b.y, o.z})) return true;
    if (rec({o.x + 1, o.y + 1, o.z + 1}, {b.x, b.y, b.z})) return true;
	  return false;
  };
  return rec({0, 0, 0}, {1000, 1000, 1000});
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    int left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
      right = sqr(std::max(p[i].x, 1000 - p[i].x)) + 
              sqr(std::max(p[i].y, 1000 - p[i].y)) +
              sqr(std::max(p[i].z, 1000 - p[i].z));
    }
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (check(mid)) left = mid;
      else right = mid - 1;
    }
    printf("Case #%d: %d\n", cas, left);
  }
  return 0;
}
#include <cstdio>
#include <vector>

using int64 = long long;

struct point {
  int64 x, y;
  point(int64 x = 0, int64 y = 0): x(x), y(y) {}
  point operator - (const point& rhs) const {
    return {x - rhs.x, y - rhs.y};
  }
  point operator + (const point& rhs) const {
    return {x + rhs.x, y + rhs.y};
  }
  int64 det(const point& rhs) const {
    return x * rhs.y - y * rhs.x;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<point> a(n), b(m);
  int s = -1, t = -1;
  for (int i = n - 1; i >= 0; --i) {
    scanf("%lld%lld", &a[i].x, &a[i].y);
    if (s == -1 || (a[i].y < a[s].y || (a[i].y == a[s].y && a[i].x < a[s].x))) s = i;
  }
  for (int i = m - 1; i >= 0; --i) {
    scanf("%lld%lld", &b[i].x, &b[i].y);
    if (t == -1 || (b[i].y < b[t].y || (b[i].y == b[t].y && b[i].x < b[t].x))) t = i;
  }
  point p{0, 0};
  int64 ret = 0;
  for (int i = 0, j = 0; i < n || j < m; ) {
    point da = a[(i + s + 1) % n] - a[(i + s) % n];
    point db = b[(j + t + 1) % m] - b[(j + t) % m];
    int64 det = da.det(db);
    if (i == n || det <= 0) p = p + db, ret += p.det(p + db), ++j;
    else p = p + da, ret += p.det(p + da), ++i;
  }
  printf("%lld\n", ret);
  return 0;
}

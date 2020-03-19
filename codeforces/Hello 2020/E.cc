#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 2501;

struct point {
  int x, y;
  point(int x = 0, int y = 0): x(x), y(y) {}
  int64 det(const point &rhs) const {
    return (int64)x * rhs.y - (int64)y * rhs.x;
  }
} p[N], q[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].x, &p[i].y);
  }
  int64 ret = (int64)n * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 24;
  for (int i = 0; i < n; ++i) {
    int m = 0;
    for (int j = 0; j < n; ++j) if (i != j) {
      q[m++] = point(p[j].x - p[i].x, p[j].y - p[i].y);
    }
    std::sort(q, q + m, [](const point &a, const point &b) {
      int sa = a.y > 0 || (a.y == 0 && a.x >= 0);
      int sb = b.y > 0 || (b.y == 0 && b.x >= 0);
      if (sa == sb) return a.det(b) > 0;
      else return sa > sb;
    });
    for (int u = 0, v = u + 1; u < m; ++u) {
      while (v != u && q[u].det(q[v]) > 0) v = (v + 1) % m;
      int cnt = v <= u ? u - v : u + m - v;
      ret -= (int64)cnt * (cnt - 1) * (cnt - 2) / 6;
    }
  }
  printf("%lld\n", ret);
  return 0;
}

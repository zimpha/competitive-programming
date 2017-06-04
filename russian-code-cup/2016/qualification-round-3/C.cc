#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    int l = 0;
    while (l * (l - 1) / 2 < k) ++l;
    int d = k - (l - 1) * (l - 2) / 2;
    std::vector<std::pair<int, int>> pt = {{0, 0}};
    int sgn = 1, dx = l, dy = 2, x = 0, y = 0;
    for (int i = 0; i < l; ++i) {
      x += sgn * dx;
      pt.emplace_back(x, y);
      if (i == l - 1) {
        y -= sgn * (d * 2 + 1);
      } else {
        y -= sgn * dy;
      }
      pt.emplace_back(x, y);
      sgn = sgn * -1;
      dx -= 1;
      dy += 2;
    }
    std::reverse(pt.begin(), pt.end());
    int x1 = 0, y1 = 0, x2 = l, y2 = 0;
    for (auto &&e: pt) {
      y1 = std::min(y1, e.second);
      y2 = std::max(y2, e.second);
    }
    for (int i = 0, d = 0; i < n - l * 2; ++i) {
      if (d == 0) y1 -= 1, pt.emplace_back(x1, y1);
      if (d == 1) x2 += 1, pt.emplace_back(x2, y1);
      if (d == 2) y2 += 1, pt.emplace_back(x2, y2);
      if (d == 3) x1 -= 1, pt.emplace_back(x1, y2);
      d = (d + 1) % 4;
    }
    x1 = y1 = 0;
    for (auto &&e: pt) {
      x1 = std::min(x1, e.first);
      y1 = std::min(y1, e.second);
    }
    std::reverse(pt.begin(), pt.end());
    for (auto &&e: pt) printf("%d %d\n", e.first - x1 + 1, e.second - y1 + 1);
  }
  return 0;
}

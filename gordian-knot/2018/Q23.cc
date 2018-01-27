#include <cstdio>
#include <utility>
#include <set>
#include <algorithm>

int main() {
  const int n = 10;
  const int d = 10000;
  std::set<std::pair<int, int>> s;
  for (int x = -2000; x <= 2000; ++x) {
    for (int y = -2000; y <= 2000; ++y) {
      int dx = x * n + 5 - 2, dy = y * n - 3;
      if (abs(y) % 2 == 0) dy += 6;
      else dy += 4;
      if (1ll * dx * dx + 1ll * dy * dy <= d * d) {
        int g = std::__gcd(abs(dx), abs(dy));
        s.emplace(dx / g, dy / g);
      }
    }
  }
  printf("%d\n", (int)s.size());
  return 0;
}

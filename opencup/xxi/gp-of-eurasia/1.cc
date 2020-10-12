#include <cstdio>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, r, c, s;
    scanf("%d%d%d%d%d", &n, &m, &r, &c, &s);

    auto inside = [&](int x, int y) {
      return std::abs(x - r) + std::abs(y - c) <= s;
    };

    if ((!inside(r, 1) && !inside(n, c)) || (!inside(1, c) && !inside(r, m))) {
      puts("Barsik");
    } else {
      puts("Tuzik");
    }
  }
  return 0;
}

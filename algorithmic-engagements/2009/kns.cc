#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int u, v, x1, y1, x2, y2;
    scanf("%d%d%d%d%d%d", &u, &v, &x1, &y1, &x2, &y2);
    if (u > v) std::swap(u, v);
    int g = gcd(u, v);
    int x = std::abs(x1 - x2);
    int y = std::abs(y1 - y2);
    u /= g; v /= g;
    if (x % g || y % g) puts("NIE");
    else if (u % 2 == v % 2) {
      x /= g, y /= g;
      if (x % 2 == y % 2) puts("TAK");
      else puts("NIE");
    } else {
      puts("TAK");
    }
  }
  return 0;
}

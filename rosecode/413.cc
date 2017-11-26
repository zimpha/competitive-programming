#include <cmath>
#include <cassert>
#include <cstdio>
#include <algorithm>

using int64 = long long;

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

int main() {
  const int64 n = 466;
  const int64 a = 4 * n * n + 12 * n - 3;
  const int64 b = 32 * (n + 3);
  for (int64 x = 1; x <= 1000000; ++x) {
    int64 y2 = -x * x * x + a * x * x - b * x;
    int64 y = sqrt(y2);
    while (y * y <= y2) ++y;
    while (y * y > y2) --y;
    if (y * y == y2) {
      assert(y * y == -x * x * x + a * x * x - b * x);
      printf("(%lld, %lld): ", x, y);
      int64 u = 8 * (n + 3) + x + y;
      int64 v = 8 * (n + 3) + x - y;
      int64 w = 2 * (-4 * (n + 3) + (n + 2) * x);
      int64 g = gcd(std::abs(u), gcd(std::abs(v), std::abs(w)));
      if (u > v) std::swap(u, v);
      if (u > w) std::swap(u, w);
      if (v > w) std::swap(v, w);
      printf("%lld,%lld,%lld\n", u / g, v / g, w / g);
      break;
    }
  }
  return 0;
}

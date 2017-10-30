// http://mathafou.free.fr/pbg_en/sol113.html
#include <cstdio>
#include <cassert>
#include <cmath>

using int64 = long long;

int64 sqr(int64 x) {return x * x;}

int64 isqrt(int64 n) {
  if (n == 0) return 0;
  int64 x = sqrt(n);
  while (true) {
    int64 y = (x + n / x) >> 1;
    if (y >= x) break;
    x = y;
  }
  while (x * x < n) ++x;
  while (x * x > n) --x;
  return x;
}

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

int64 gcd(int64 a, int64 b, int64 c, int64 d) {
  return gcd(gcd(a, b), gcd(c, d));
}

bool valid(int x, int y, int z, int t) {
  return gcd(x, y, z, t) == 1 && z * z <= y * y + x * x + x * y;
}

void solve(int n) {
  int64 cnt = 0, sum = 0;
  for (int64 t = 1; t <= n; ++t) {
    int64 t2 = sqr(t), t4 = sqr(t2);
    for (int64 x = 1; x < t; ++x) {
      int64 x2 = sqr(x), x4 = sqr(x2);
      for (int64 y = x; y < t; ++y) {
        if (x + y <= t) continue;
        int64 y2 = sqr(y), y4 = sqr(y2);
        int64 delta = 6 * (t2 * x2 + t2 * y2 + x2 * y2) - 3 * (t4 + x4 + y4);
        if (delta < 0) continue;
        int64 sq = isqrt(delta);
        if (sq * sq != delta) continue;
        if ((t2 + x2 + y2 + sq) % 2 == 0) {
          int64 z1 = (t2 + x2 + y2 - sq) / 2;
          int64 z2 = (t2 + x2 + y2 + sq) / 2;
          if (z1 >= y2 && z1 < t2) {
            int64 z = isqrt(z1);
            if (z * z == z1 && valid(x, y, z, t)) {
              ++cnt, sum += t + x + y + z;
              printf("%lld %lld %lld %lld\n", x, y, z, t);
            }
          }
          if (z2 >= y2 && z2 < t2 && sq) {
            int64 z = isqrt(z2);
            if (z * z == z2 && valid(x, y, z, t)) {
              ++cnt, sum += t + x + y + z;
              printf("%lld %lld %lld %lld\n", x, y, z, t);
            }
          }
        }
      }
    }
  }
  printf("%lld,%lld\n", cnt, sum);
}

int main() {
  solve(200);
  solve(5000);
  return 0;
}

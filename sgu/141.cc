#include <cstdio>
#include <algorithm>

using int64 = long long;

// ax + by = gcd(a, b), |x| + |y| is minimum
void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

int main() {
  int64 x1, x2, p, k;
  scanf("%lld%lld%lld%lld", &x1, &x2, &p, &k);
  int64 x, y, g;
  exgcd(x1, x2, g, x, y);
  if (p % g) {
    puts("NO");
    return 0;
  }
  x *= p / g, y *= p / g;
  int64 d1 = x2 / g, d2 = x1 / g;
  while (abs(x + d1) + abs(y - d2) < abs(x) + abs(y)){
    x += d1, y -= d2;
  }
  while (abs(x - d1) + abs(y + d2) < abs(x) + abs(y)) {
    x -= d1, y += d2;
  }
  if (abs(x) + abs(y) > k) {
    puts("NO");
    return 0;
  }
  if ((k - abs(x) - abs(y)) & 1) {
    if (abs(d1 + d2) % 2 == 0) {
      puts("NO");
      return 0;
    }
    if (abs(x + d1) + abs(y - d2) < abs(x - d1) + abs(y + d2)) {
      x += d1, y -= d2;
    } else {
      x -= d1, y += d2;
    }
    if (abs(x) + abs(y) > k) {
      puts("NO");
      return 0;
    }
  }
  int64 t = (k - abs(x) - abs(y)) / 2;
  int64 p1, p2, n1, n2;
  if (x < 0) p1 = t, n1 = t + abs(x);
  else p1 = t + x, n1 = t;
  if (y < 0) p2 = 0, n2 = -y;
  else p2 = y, n2 = 0;
  puts("YES");
  printf("%lld %lld %lld %lld\n", p1, n1, p2, n2);
  return 0;
}

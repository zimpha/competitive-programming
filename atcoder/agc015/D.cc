#include <cstdio>
#include <algorithm>

using int64 = long long;

int64 solve(int64 a, int64 b) {
  if (a == b) return 1;
  int k = 0;
  while ((a >> k) != (b >> k)) ++k;
  printf("%lld %lld %d\n", a, b, k);
  a &= (1 << k) - 1;
  b &= (1 << k) - 1;
  int64 c = 1ll << (k - 1);
  printf("%lld %lld %d c=%lld\n", a, b, k, c);
  // [a, c) + [c + a, 2c)
  if (c + a - 1 <= b || a == 0) return c * 2 - a;
  else return (c - a) * 2 + solve(c, b);
}
/*
21: 0101
26: 1010
 101  110  111
1101 1110 1111
1000 1001
1010 1011
*/

int main() {
  int64 a, b;
  scanf("%lld%lld", &a, &b);
  printf("%lld\n", solve(a, b));
  return 0;
}

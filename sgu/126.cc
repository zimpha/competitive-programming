#include <cstdio>

using int64 = long long;

int64 gcd(int64 a, int64 b) {
  return !b ? a : gcd(b, a % b);
}

int main() {
  int64 a, b;
  scanf("%lld%lld", &a, &b);
  int64 g = gcd(a, b);
  int64 c = (a + b) / g;
  if (c & (c - 1)) puts("-1");
  else {
    printf("%d\n", __builtin_ctz(c));
  }
  return 0;
}

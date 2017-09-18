#include <cstdio>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int s = 1;
  for (int i = 0; i < k; ++i) s *= 10;
  int g = gcd(s, n);
  printf("%lld\n", 1ll * s / g * n);
  return 0;
}

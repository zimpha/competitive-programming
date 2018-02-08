#include <cstdio>

int main() {
  long long n, x = 0;
  scanf("%lld", &n);
  while ((1ll << (x + 1)) * (x + 1) <= n) ++x;
  printf("%lld\n", x);
  return 0;
}

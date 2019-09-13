#include <cmath>
#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int v = sqrt(n);
  long long r = 0;
  for (int x = 1; x <= v; ++x) {
    r += n / x;
  }
  printf("%lld\n", r - v * (v - 1) / 2);
  return 0;
}

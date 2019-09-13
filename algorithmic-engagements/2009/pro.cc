#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int r = 0;
  for (int x = 1; x <= n; ++x) {
    r += n / x;
    if (x * x <= n) ++r;
  }
  printf("%d\n", r / 2);
  return 0;
}

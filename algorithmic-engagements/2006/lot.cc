#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int r = 1, zero = true;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    if (x) zero = false;
    r = r * (x + 1) % 9;
  }
  r = (r + 8) % 9;
  if (r == 0) r = 9;
  if (zero) r = 0;
  printf("%d\n", r);
  return 0;
}

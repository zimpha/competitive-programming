#include <cstdio>

int main() {
  int x, l, r;
  scanf("%d%d%d", &x, &l, &r);
  if (x < l) x = l;
  else if (x > r) x = r;
  printf("%d\n", x);
  return 0;
}

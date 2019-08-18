#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  if (n == 1) puts("0");
  else if (n == 2) puts("1");
  else if (n == 3) puts("3");
  else printf("%d\n", 3 * (n - 2));
  for (int i = 0; i < n; ++i) {
    if (i == 0) printf("%d %d %d\n", i, 0, 1000000000);
    else if (i == 1) printf("%d %d %d\n", i, 100000000, 200000000);
    else printf("%d %d %d\n", i, 100000000 - i, 100000000 + i);
  }
  return 0;
}

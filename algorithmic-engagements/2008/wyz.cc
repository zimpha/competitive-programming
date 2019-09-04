#include <cstdio>

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  if (d == 0 || (d == 1 && n != 2)) {
    puts("BRAK");
    return 0;
  }
  if (d == 1 && n == 2) {
    puts("1 2");
    return 0;
  }
  if (d == 2) {
    for (int i = 2; i <= n; ++i) {
      printf("1 %d\n", i);
    }
    return 0;
  }
  d -= 2;
  for (int i = 1; i <= d; ++i) {
    printf("%d %d\n", i, i + 1);
  }
  for (int i = d + 2; i <= n; ++i) {
    if (i & 1) printf("1 %d\n", i);
    else printf("%d %d\n", i, d + 1);
  }
  return 0;
}

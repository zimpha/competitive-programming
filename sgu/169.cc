#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  if (n == 1) puts("8");
  else if ((n - 1) % 6 == 0) puts("4");
  else if ((n - 1) % 3 == 0) puts("3");
  else puts("1");
  return 0;
}

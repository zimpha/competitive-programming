#include <cstdio>

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  int cnt = (a == 1) + (b == 1) + (c == 1);
  if (cnt >= 2) puts("1");
  else puts("2");
  return 0;
}

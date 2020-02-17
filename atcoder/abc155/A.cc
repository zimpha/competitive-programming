#include <cstdio>

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  if ((a == b && a != c) || (a == c && a != b) || (b == c && a != b)) puts("Yes");
  else puts("No");
  return 0;
}

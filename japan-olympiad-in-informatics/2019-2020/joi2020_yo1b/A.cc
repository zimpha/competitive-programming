#include <cstdio>
#include <algorithm>

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  if (b < c) std::swap(b, c);
  if (a < b) std::swap(a, b);
  if (b < c) std::swap(b, c);
  printf("%d\n", a + b);
  return 0;
}

#include <cstdio>
#include <algorithm>

int main() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  printf("%d %d\n", std::min(a, b), std::max(0, a + b - n));
  return 0;
}

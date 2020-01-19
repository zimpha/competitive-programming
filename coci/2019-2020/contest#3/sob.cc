#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int a = n - 1, b = m; a >= 0; ) {
    while ((a & b) != a) ++b;
    for (int i = b; i >= m; --i) {
      printf("%d %d\n", a - (b - i), i);
    }
    a -= (b - m + 1);
    b = m = b + 1;
  }
  return 0;
}

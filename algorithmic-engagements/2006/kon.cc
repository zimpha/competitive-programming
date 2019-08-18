#include <cstdio>

int main() {
  int a = 1, b = 1, n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int c = (a + b) % 10;
    a = b;
    b = c;
  }
  printf("%d\n", b);
  return 0;
}

#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    if (n % i) {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("%d\n", n + 1);
  return 0;
}

#include <cstdio>

int main() {
  int n; scanf("%d", &n);
  if (n == 2) {
    puts("3 4\n5 2 3");
    return 0;
  }
  printf("%d", n);
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      if (i + j > n + 2) printf(" %d", j + (i - 1) * n);
    }
  }
  puts("");
  int s = n + 1 + n % 2;
  printf("%d", s); s += 2;
  for (int i = 2; i <= n; ++ i) printf(" %d", (i - 1) * n + n - i + 2);
  puts("");
  for (int j = n; j >= 2; -- j, s += 2) {
    printf("%d", s);
    for (int i = 1; i <= j; ++ i) printf(" %d", (i - 1) * n + j - i + 1);
    puts("");
  }
  return 0;
}

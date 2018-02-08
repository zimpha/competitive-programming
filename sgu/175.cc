#include <cstdio>

int phi(int n, int q) {
  if (n == 1) return 1;
  int m = n / 2;
  if (q <= m) return n - m + phi(m, m + 1 - q);
  else return phi(n - m, n + 1 - q);
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  printf("%d\n", phi(n, q));
  return 0;
}

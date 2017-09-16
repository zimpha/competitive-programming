#include <cstdio>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int b = 1; b < n; ++b) {
    if (n - b >= b) continue;
    if (gcd(n - b, b) == 1) {
      printf("%d %d\n", n - b, b);
      break;
    }
  }
  return 0;
}
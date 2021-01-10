#include <cstdio>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int r, b;
    scanf("%d%d", &r, &b);
    int y = (r + b) * (r + b - 1) / 2;
    int x = r * (r - 1) / 2;
    int g = gcd(x, y);
    printf("Case #%d: %d/%d\n", cas, x / g, y / g);
  }
  return 0;
}

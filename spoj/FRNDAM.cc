#include <cstdio>

int dsum(int n) {
  int r = 0;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      r += i;
      if (i * i != n) r += n / i;
    }
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int x, y;
    scanf("%d%d", &x, &y);
    int sx = dsum(x) - x;
    int sy = dsum(y) - y;
    if (sx == y && sy == x) puts("Friendship is ideal");
    else puts("Friendship is not ideal");
  }
  return 0;
}

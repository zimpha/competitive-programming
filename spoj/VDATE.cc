#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x < y) puts("0");
    else if (x == y) puts("-1");
    else {
      int m = x - y;
      int ret = 0;
      for (int i = 1; i * i <= m; ++i) {
        if (m % i == 0) {
          if (x % i == y) ++ret;
          if (i * i != m && x % (m / i) == y) ++ret;
        }
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}

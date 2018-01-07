#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int p, q, c;
    scanf("%d%d%d", &p, &q, &c);
    int n;
    scanf("%d", &n);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      if ((int64)x * x + (int64)y * y - (int64)x * p - (int64)y * q + c <= 0) ++ret;
    }
    printf("%d\n", ret);
  }
  return 0;
}

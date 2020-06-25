#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k, x, y;
    scanf("%d%d%d%d", &n, &k, &x, &y);
    int cx = 0, cy = 0;
    for (int i = 0, d; i < n; ++i) {
      scanf("%d", &d);
      cx += d >= x;
      cy += d >= y;
    }
    if (x >= y) {
      if (cx >= 2 && cy - 2 >= k) puts("YES");
      else puts("NO");
    } else {
      if (cy >= k && cx - k >= 2) puts("YES");
      else puts("NO");
    }
  }
  return 0;
}

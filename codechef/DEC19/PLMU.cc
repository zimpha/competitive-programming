#include <cstdio>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int c0 = 0, c2 = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      c0 += x == 0;
      c2 += x == 2;
    }
    printf("%d\n", c0 * (c0 - 1) / 2 + c2 * (c2 - 1) / 2);
  }
  return 0;
}

#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, cnt = 0;
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      cnt += x != 1;
    }
    if (n / 2 < cnt) cnt = n / 2;
    if (n == 2) cnt = 1;
    printf("%d\n", cnt);
  }
  return 0;
}

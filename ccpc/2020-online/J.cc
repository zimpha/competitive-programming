#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int last = -1, valid = 1;
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      valid &= last != x;
      last = x;
    }
    if (valid) puts("YES");
    else puts("NO");
  }
  return 0;
}

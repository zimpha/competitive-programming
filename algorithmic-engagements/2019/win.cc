#include <cstdio>
#include <algorithm>

int main() {
  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    int ret = 2019;
    for (int i = 0; i < n; ++i) {
      for (int j = 0, x; j <= i; ++j) {
        scanf("%d", &x);
        int cnt = (j + 1) * (i - j + 1);
        if (cnt <= k) ret = std::min(ret, x);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

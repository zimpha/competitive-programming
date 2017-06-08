#include <cstdio>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int k, x, y;
    scanf("%d%d%d", &k, &x, &y);
    if (x > y) {
      int e = std::max(y + 2, k);
      printf("%d\n", e - x);
    } else {
      int e = std::max(x + 2, k);
      printf("%d\n", e - y);
    }
  }
  return 0;
}

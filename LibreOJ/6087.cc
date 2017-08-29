#include <cstdio>
#include <algorithm>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k == 1) {
    int r = 0, x;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &x);
      r ^= x;
    }
    printf("%d\n", r);
  } else {
    int x[32], y[32], r = 0;
    for (int i = 0; i < 32; ++i) {
      x[i] = y[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      int v;
      scanf("%d", &v);
      r ^= v;
      for (int b = 0; b < 31; ++b) {
        if (v >> b & 1) x[b] ^= v;
        else y[b] ^= v;
      }
    }
    for (int i = 0; i < 31; ++i) {
      if (r >> i & 1) {
        if (x[i] > y[i]) {
          std::swap(x[i], y[i]);
        }
        printf("%d %d\n", x[i], y[i]);
        break;
      }
    }
  }
  return 0;
}

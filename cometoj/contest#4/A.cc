#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a[5];
    for (int i = 0; i < 5; ++i) a[i] = 0;
    for (int i = 0; i < 5; ++i) {
      int x;
      scanf("%d", &x);
      a[x - 1]++;
    }
    int best = 0;
    for (int i = 0; i < 5; ++i) {
      if (a[i] > a[best]) best = i;
    }
    printf("%d\n", best + 1);
  }
  return 0;
}

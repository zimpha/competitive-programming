#include <stdio.h>
int l[1<<20], b[1<<20], v[1 << 20];
int main() {
  int T, cas=0; scanf("%d", &T);
  while (T --) {
    int n, m = 0; scanf("%d", &n); ++ cas;
    for (int i = 0; i < n; ++ i) {
      int x; scanf("%d", &x);
      l[i] = i; v[i] = x; m |= x;
      for (int j = i; j >= 0; j = l[j] - 1) {
        v[j] = v[j] | x;
        while (l[j] >= 1 && (x | v[l[j] - 1]) == (x | v[j])) l[j] = l[l[j] - 1];
        if (b[v[j]] != cas) b[v[j]] = cas;
      }
    }
    n = 0;
    for (int i = 0; i <= m; ++ i) n += b[i] == cas;
    printf("%d\n", n);
  }
  return 0;
}


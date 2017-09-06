#include <cstdio>

int main() {
  int n, k, t;
  scanf("%d%d%d", &n, &k, &t);
  if (t <= k) printf("%d\n", t);
  else if (t > n) printf("%d\n", n + k - t);
  else printf("%d\n", k);
  return 0;
}
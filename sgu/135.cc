#include <cstdio>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  int64 r = 1;
  for (int i = 1; i <= n; ++i) r += i;
  printf("%lld\n", r);
  return 0;
}

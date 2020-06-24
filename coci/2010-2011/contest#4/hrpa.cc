#include <cstdio>

using int64 = long long;

int main() {
  int64 n;
  scanf("%lld", &n);
  int64 ret = -1;
  while (n) {
    int64 a = 0, b = 1;
    while (true) {
      int64 c = a + b;
      a = b; b = c;
      if (b > n) break;
    }
    ret = a;
    n -= a;
  }
  printf("%lld\n", ret);
  return 0;
}

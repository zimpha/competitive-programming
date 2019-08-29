#include <cmath>
#include <cstdio>

using int64 = long long;

int main() {
  int64 n;
  scanf("%lld", &n);
  int64 ret = 0;
  for (int x = 1; x <= n / x; ++x) {
    ret += n / x;
  }
  int64 v = sqrt(n);
  ret = ret * 2 - v * v;
  printf("%lld\n", ret);
  return 0;
}

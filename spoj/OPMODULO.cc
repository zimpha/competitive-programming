#include <cstdio>

using int64 = long long;

int main() {
  int64 l, r;
  scanf("%lld%lld", &l, &r);
  int64 s = 1;
  int64 ret = 0;
  for (; s <= r; s *= 2) ret += (s >= l) * s;
  printf("%lld\n", ret);
  return 0;
}

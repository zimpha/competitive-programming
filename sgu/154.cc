#include <cstdio>

using int64 = long long;

int main() {
  auto count = [](int64 n) {
    int64 ret = 0;
    for (int64 p = 5; p <= n; p *= 5) ret += n / p;
    return ret;
  };
  int q;
  scanf("%d", &q);
  int l = 1, r = q * 5;
  while (l < r) {
    int m = (l + r - 1) >> 1;
    if (count(m) >= q) r = m;
    else l = m + 1;
  }
  if (count(l) == q) printf("%d\n", l);
  else puts("No solution");
  return 0;
}

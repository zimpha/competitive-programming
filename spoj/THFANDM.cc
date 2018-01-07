#include <cstdio>
#include <cassert>
#include <algorithm>

using int64 = long long;

int64 x, t, p, q, v;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    assert(scanf("%lld%lld%lld%lld%lld", &x, &p, &q, &t, &v) == 5);
    assert(x - q <= p && p <= x + q);
    int64 s = p + v * t - q;
    printf("%lld\n", std::max<int64>(s - x, 0));
  }
  return 0;
}

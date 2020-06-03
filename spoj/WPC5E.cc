#include <cstdio>
#include <algorithm>

using int64 = long long;

const int64 inf = 1ll << 61;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int64 mx[4] = {-inf, -inf, -inf, -inf};
    int64 ret = 0;
    for (int i = 0; i < n; ++i) {
      int64 x[2];
      scanf("%lld", &x[1]);
      x[0] = (int64)(i + 1) * (i + 1);
      x[1] *= x[1];
      for (int mask = 0; mask < 4; ++mask) {
        int64 now = 0;
        for (int k = 0; k < 2; ++k) {
          if (mask >> k & 1) now += x[k];
          else now -= x[k];
        }
        ret = std::max(ret, now + mx[~mask & 3]);
      }
      for (int mask = 0; mask < 4; ++mask) {
        int64 now = 0;
        for (int k = 0; k < 2; ++k) {
          if (mask >> k & 1) now += x[k];
          else now -= x[k];
        }
        mx[mask] = std::max(mx[mask], now);
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}

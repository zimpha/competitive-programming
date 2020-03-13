#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 998244353;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int64> a(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
  int64 x = 0, ret = 0;
  for (int i = 0; i < n; ++i) {
    if ((x & a[i]) != a[i]) {
      int64 ways = 0, extra = 0;
      for (int j = 0; j < k; ++j) {
        if ((~a[i] >> j & 1) && (~x >> j & 1)) ++extra;
      }
      for (int j = 0; j < k; ++j) if (a[i] >> j & 1) {
        if (x >> j & 1) continue;
        int ones = __builtin_popcountll(a[i] >> (j + 1));
        int match = __builtin_popcountll((x & a[i]) >> (j + 1));
        ways += int64(1) << (ones - match);
      }
      ret += (ways << extra) % mod * (i + 1) % mod;
    }
    x |= a[i];
  }
  printf("%lld\n", ret % mod);
  return 0;
}

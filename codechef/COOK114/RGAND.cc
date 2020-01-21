#include <cstdio>

using int64 = long long;

const int mod = 1e9 + 7;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 l, r;
    scanf("%lld%lld", &l, &r);
    int64 ret = 0;
    for (int i = 0; i <= 60; ++i) if (l >> i & 1) {
      auto v = ((l >> i) << i) + (int64(1) << i) - 1;
      if (v > r) v = r;
      ret += (int64(1) << i) % mod * ((v - l + 1) % mod) % mod;
      ret %= mod;
    }
    printf("%lld\n", ret);
  }
  return 0;
}

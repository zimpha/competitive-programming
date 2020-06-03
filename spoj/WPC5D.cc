#include <cstdio>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  a %= mod;
  if (a < 0) a += mod;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    int64 ret = k * pow_mod(k - 2, n) % mod - 2 * pow_mod(k, n) % mod + pow_mod(k, n + 1);
    ret %= mod;
    ret += mod;
    ret %= mod;
    printf("%lld\n", (k - 1) * ret % mod * pow_mod(2, mod - 2) % mod * pow_mod(k - 2, mod - 2) % mod * pow_mod(k, mod - 2) % mod);
  }
  return 0;
}

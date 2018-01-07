#include <cstdio>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
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
    int64 n, p;
    scanf("%lld%lld", &n, &p);
    printf("%lld %lld\n", (pow_mod(p, n) + mod - 1) * pow_mod(p - 1, mod - 2) % mod, pow_mod(p, n - 1));
  }
  return 0;
}

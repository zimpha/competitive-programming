#include <cstdio>

using i64 = long long;

const int mod = 998244353;

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  printf("%lld\n", pow_mod(n, m - 1) * pow_mod(m, n - 1) % mod);
  return 0;
}

#include <cstdio>

using int64 = unsigned long long;

const int mod = 998244353;

int64 pow_mod(int64 a, int n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int64 n, k;
  scanf("%lld%lld", &n, &k);
  int64 g = pow_mod(3, (mod - 1) / k), wn = 1;
  int64 ret = 0;
  n %= mod - 1;
  for (int i = 0; i < k; ++i, wn = wn * g % mod) {
    ret += pow_mod(wn + 1, n);
  }
  printf("%llu\n", pow_mod(k, mod - 2) * (ret % mod) % mod);
  return 0;
}

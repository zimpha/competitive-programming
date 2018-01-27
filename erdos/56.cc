#include <cstdio>
#include <vector>

using uint64 = unsigned long long;

const uint64 mod = 1e9 + 7;

uint64 pow_mod(uint64 a, uint64 n) {
  uint64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  const int n = 314159;
  std::vector<uint64> fac(n + 1, 1), ifac(n + 1, 1), p2(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
    p2[i] = p2[i - 1] * pow_mod(2, mod - 2) % mod;
  }
  uint64 ret = 0;
  for (int a = 0; a <= n; ++a) {
    for (int b = 0; a + b <= n; ++b) {
      int c = n - a - b;
      if (a + 2 * b + 3 * c != n * 2 - 2) continue;
      ret += p2[c] * ifac[a] % mod * ifac[b] % mod * ifac[c] % mod;
    }
    ret %= mod;
  }
  ret = ret * fac[n] % mod * fac[n - 2] % mod;
  printf("%llu\n", ret);
  return 0;
}

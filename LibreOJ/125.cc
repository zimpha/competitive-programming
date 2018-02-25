#include <cmath>
#include <vector>
#include <cstdio>

using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

int main() {
  constexpr int mod = 998244353;
  uint32 n;
  scanf("%u", &n);
  uint32 v = sqrt(n);
  uint64 s0 = 0, s1 = 0;
  uint128 s2 = 0;
  for (uint32 beg : {1, 5}) for (uint32 i = beg; i <= v; i += 6) {
    for (uint32 M = n / i, j = i; j <= v; j *= 3, M /= 3) {
      for (uint32 L = M, k = j; k <= v; k <<= 1, L >>= 1) {
        s0 += L;
        s1 += uint64(L) * (2 * k + L + 1);
        s2 += uint128(L) * (uint64(L + 1) * (2 * L + 1) + 6ull * k * k);
      }
    }
  }
  s2 -= uint128(v) * v * (v + 1) * (2 * v + 1); s2 /= 6;
  s1 -= uint64(v) * v * (v + 1); s1 /= 2;
  s0 = s0 * 2 - v * v;
  printf("%d\n", int((s0 * 5 + s1 * 3 + s2 * 2) % mod));
  return 0;
}

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

const uint32 mod = 1e9 + 7;

int main() {
  uint64 n;
  scanf("%llu", &n);
  const uint32 v = static_cast<uint32>(sqrtl(n));
  std::vector<uint64> ssum(v + 1), lsum(v + 1);
  std::vector<uint64> scnt(v + 1), lcnt(v + 1);
  std::vector<uint32> primes;
  for (uint32 i = 1; i <= v; ++i) {
    scnt[i] = i - 1;
    lcnt[i] = n / i - 1;
    ssum[i] = (uint128)i * (i + 1) / 2 - 1;
    lsum[i] = (uint128)(n / i) * (n / i + 1) / 2 - 1;
  }
  for (uint32 p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    primes.push_back(p);
    const uint64 psum = ssum[p - 1], pcnt = scnt[p - 1];
    const uint64 q = (uint64)p * p;
    const uint32 ed = std::min<uint64>(v, n / q);
    for (uint32 i = 1, w = v / p; i <= w; ++i) {
      const uint32 d = i * p;
      lsum[i] -= (lsum[d] - psum) * p;
      lcnt[i] -= lcnt[d] - pcnt;
    }
    if (n / p < std::numeric_limits<uint32>::max()) {
      const uint32 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) {
        uint32 d = m / i;
        lsum[i] -= (ssum[d] - psum) * p;
        lcnt[i] -= scnt[d] - pcnt;
      }
    } else {
      const uint64 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) {
        uint32 d = m / i;
        lsum[i] -= (ssum[d] - psum) * p;
        lcnt[i] -= scnt[d] - pcnt;
      }
    }
    for (uint32 i = v; i >= q; --i) {
      const uint32 d = i / p;
      ssum[i] -= (ssum[d] - psum) * p;
      scnt[i] -= scnt[d] - pcnt;
    }
  }
  for (uint32 i = 1; i <= v; ++i) {
    lsum[i] -= lcnt[i];
    ssum[i] -= scnt[i];
    if (n >= i * 2) lsum[i] += 2;
    if (i >= 2) ssum[i] += 2;
  }
  primes.push_back(v + 1);

  std::function<uint64(uint64, uint32, uint64)> rec = [&](uint64 rest, uint32 last, uint64 mul) {
    uint64 t = ((rest > v ? lsum[n / rest] : ssum[rest]) - ssum[primes[last] - 1]) % mod;
    uint64 ret = mul * t % mod;
    for (uint32 i = last; i < primes.size(); ++i) {
      uint32 p = primes[i];
      if (uint64(p) * p > rest) break;
      uint32 e = 1;
      for (uint64 q = p, nrest = rest; q * p <= rest; q *= p) {
        uint64 nmul = mul * (p ^ e) % mod;
        ret += rec(nrest /= p, i + 1, nmul);
        ret += mul * (p ^ (++e));
      }
    }
    return ret % mod;
  };
  uint64 ret = 1;
  if (n > 1) ret += rec(n, 0, 1);
  printf("%llu\n", ret % mod);
  return 0;
}

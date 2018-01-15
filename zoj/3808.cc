#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

using uint32 = unsigned int;
using uint64 = unsigned long long;

template <typename U, typename DU>
struct FastDiv {
  static constexpr int S = sizeof(U) * 8;
  FastDiv() {}
  FastDiv(U n) : m(n) {
    s = std::__lg(n - 1);
    x = ((DU(1) << (s + S)) + n - 1) / n;
  }
  friend U operator / (U n, FastDiv d) { 
    return (DU(n) * d.x >> d.s) >> S; 
  }
  friend U operator % (U n, FastDiv d) { return n - n / d * d.m; }
  U m, x; int s;
};

const int N = 1e5;

uint64 ssum[N], lsum[N];
uint32 scnt[N], lcnt[N];
uint32 primes[N], pcnt;
FastDiv<uint32, uint64> fdiv[N];

uint64 count(uint32 n) {
  const uint32 v = static_cast<uint32>(sqrtl(n));
  for (uint32 i = 1; i <= v; ++i) {
    fdiv[i] = i;
    scnt[i] = i - 1;
    lcnt[i] = n / i - 1;
    ssum[i] = (uint64)i * (i + 1) / 2 - 1;
    lsum[i] = (uint64)(n / i) * (n / i + 1) / 2 - 1;
  }
  pcnt = 0;
  for (uint32 p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    primes[pcnt++] = p;
    const uint64 psum = ssum[p - 1];
    const uint32 pcnt = scnt[p - 1];
    const uint32 q = p * p;
    const uint32 ed = std::min(v, n / q);
    for (uint32 i = 1, w = v / p; i <= w; ++i) {
      const uint32 d = i * p;
      lsum[i] -= (lsum[d] - psum) * p;
      lcnt[i] -= lcnt[d] - pcnt;
    }
    const uint32 m = n / p;
    for (uint32 i = v / p + 1; i <= ed; ++i) {
      uint32 d = m / fdiv[i];
      lsum[i] -= (ssum[d] - psum) * p;
      lcnt[i] -= scnt[d] - pcnt;
    }
    for (uint32 i = v; i >= q; --i) {
      const uint32 d = i / fdiv[p];
      ssum[i] -= (ssum[d] - psum) * p;
      scnt[i] -= scnt[d] - pcnt;
    }
  }
  for (uint32 i = 1; i <= v; ++i) {
    lsum[i] -= lcnt[i];
    ssum[i] -= scnt[i];
  }
  primes[pcnt++] = v + 1;

  std::function<uint64(uint32, uint32, uint64)> rec = [&](uint32 rest, uint32 last, uint64 mul) {
    uint64 t = ((rest > v ? lsum[n / rest] : ssum[rest]) - ssum[primes[last] - 1]);
    uint64 ret = mul * t;
    for (uint32 i = last; i < pcnt; ++i) {
      uint32 p = primes[i];
      if (p * p > rest) break;
      uint64 nmul = mul * p;
      for (uint32 q = p, nrest = rest / fdiv[p]; p <= nrest; q *= p) {
        ret += rec(nrest, i + 1, nmul - mul);
        nrest = nrest / fdiv[p];
        nmul *= p;
        ret += nmul - mul;
      }
    }
    return ret;
  };
  uint64 ret = 1;
  if (n > 1) ret += rec(n, 0, 1);
  return ret;
}

int main() {
  for (uint32 n; scanf("%u", &n) == 1; ) {
    printf("%llu\n", count(n));
  }
  return 0;
}

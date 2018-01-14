#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

using uint64 = unsigned long long;
using uint32 = unsigned int;

uint64 prime_count(uint64 n) {
  const uint32 v = static_cast<uint64>(sqrtl(n));
  std::vector<uint64> ssum(v + 1), lsum(v + 1);
  std::vector<bool> mark(v + 1);
  for (uint32 i = 1; i <= v; ++i) {
    ssum[i] = i - 1;
    lsum[i] = n / i - 1;
  }
  for (uint32 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    uint64 psum = ssum[p - 1], q = (uint64)p * p;
    uint32 ed = std::min<uint64>(v, n / q);
    uint32 delta = (p & 1) + 1;
    for (uint32 i = 1, w = v / p; i <= w; i += delta) if (!mark[i]) {
      lsum[i] -= lsum[i * p] - psum;
    }
    if (n / p < std::numeric_limits<uint32>::max()) {
      uint32 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        lsum[i] -= ssum[m / i] - psum;
      }
    } else {
      uint64 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        lsum[i] -= ssum[m / i] - psum;
      }
    }
    for (uint64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (uint32 i = v; i >= q; --i) {
      ssum[i] -= ssum[i / p] - psum;
    }
  }
  return lsum[1];
}

int main() {
  uint64 n;
  scanf("%llu", &n);
  printf("%llu\n", prime_count(n));
}

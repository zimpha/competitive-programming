#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using uint32 = unsigned int;
using uint64 = unsigned long long;

// return the sum of p^k for all p <= m, where m is in form floor(n / i)
// for m <= sqrt{n}, stored in ssum[m]; for m > sqrt{n} stored in lsum[n / m]
uint64 prime_count(uint64 n) {
  if (n < 2) return 0;
  const uint32 v = static_cast<uint32>(sqrtl(n));
  std::vector<uint64> ssum(v + 1), lsum(v + 1);
  std::vector<bool> mark(v + 1);
  for (uint32 i = 1; i <= v; ++i) {
    ssum[i] = i - 1;
    lsum[i] = n / i - 1;
  }
  for (uint32 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    uint64 psum = ssum[p - 1];
    uint64 q = (uint64)p * p;
    uint32 ed = std::min<uint64>(v, n / q);
    int delta = (p & 1) + 1;
    for (uint32 i = 1, w = v / p; i <= w; i += delta) if (!mark[i]) {
      lsum[i] -= lsum[i * p] - psum;
    }
    if (n / p < std::numeric_limits<int>::max()) {
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
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    uint64 n;
    scanf("%llu", &n);
    uint64 cnt = prime_count(n) - prime_count(n / 2) + 1;
    printf("%llu\n", n - (n - cnt) / 2);
  }
  return 0;
}

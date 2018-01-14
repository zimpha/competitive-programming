#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using uint32 = unsigned int;
using uint64 = unsigned long long;

constexpr int N = 2e5;

uint64 ssum[N + 1][2], lsum[N + 1][2];
uint32 ps[N + 1], pcnt;

void sieve() {
  for (uint32 i = 2; i <= N; ++i) {
    if (!ps[i]) ps[pcnt++] = i;
    for (uint32 j = 0, u = N / i; j < pcnt && ps[j] <= u; ++j) {
      ps[i * ps[j]] = 1;
      if (i % ps[j] == 0) break;
    }
  }
}

uint64 prime_count(uint64 n) {
  const uint32 v = static_cast<uint32>(sqrtl(n));
  auto sum = [](uint64 n, uint32 e) {
   if (n < e) return uint64(0);
   return (n - e) / 4 + 1;
  };
  for (uint32 i = 1; i <= v; ++i) {
    ssum[i][0] = sum(i, 1) - 1;
    ssum[i][1] = sum(i, 3);
    lsum[i][0] = sum(n / i, 1) - 1;
    lsum[i][1] = sum(n / i, 3);
  }
  std::vector<bool> mark(v + 1);
  for (uint32 it = 1; it < pcnt && ps[it] <= v; ++it) {
    uint32 p = ps[it];
    uint64 q = (uint64)p * p;
    uint32 ed = std::min<uint64>(v, n / q);
    uint32 o = (p & 3) == 1;
    uint64 *psum = ssum[p - 1];
    uint32 delta = (p & 1) + 1;
    for (uint32 i = 1, w = v / p; i <= w; i += delta) if (!mark[i]) {
      uint32 d = i * p;
      lsum[i][0] -= lsum[d][o ^ 1] - psum[o ^ 1];
      lsum[i][1] -= lsum[d][o] - psum[o];
    }
    if (n / p < std::numeric_limits<uint32>::max()) {
      uint32 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        uint32 d = m / i;
        lsum[i][0] -= ssum[d][o ^ 1] - psum[o ^ 1];
        lsum[i][1] -= ssum[d][o] - psum[o];
      }
    } else {
      uint64 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        uint32 d = m / i;
        lsum[i][0] -= ssum[d][o ^ 1] - psum[o ^ 1];
        lsum[i][1] -= ssum[d][o] - psum[o];
      }
    }
    for (uint64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (uint32 i = v; i >= q; --i) {
      uint32 d = i / p;
      ssum[i][0] -= ssum[d][o ^ 1] - psum[o ^ 1];
      ssum[i][1] -= ssum[d][o] - psum[o];
    }
  }
  return lsum[1][0];
}

int main() {
  sieve();
  uint64 n;
  scanf("%llu", &n);
  printf("%llu\n", prime_count(n));
  return 0;
}

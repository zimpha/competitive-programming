#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using uint32 = unsigned int;
using uint64 = unsigned long long;

constexpr uint32 N = 2e5, M = 12;

uint64 ssum[N + 1][M], lsum[N + 1][M];
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

void prime_count(uint64 n, uint64 mod) {
  const uint32 v = static_cast<uint32>(sqrtl(n));
  for (uint32 i = 1; i <= v; ++i) {
    for (uint32 j = 0; j < mod; ++j) {
      ssum[i][j] = (i >= j) ? (i - j) / mod + 1 : 0;
      lsum[i][j] = (n / i >= j) ? (n / i - j) / mod + 1 : 0;
    }
    --ssum[i][0], --lsum[i][0];
    --ssum[i][1], --lsum[i][1];
  }
  std::vector<bool> mark(v + 1);
  for (uint32 it = 0; it < pcnt && ps[it] <= v; ++it) {
    const uint32 p = ps[it];
    const uint64 q = (uint64)p * p;
    const uint32 ed = std::min<uint64>(v, n / q);
    const uint32 delta = (p & 1) + 1;
    uint64 *psum = ssum[p - 1];
    uint32 next[mod] = {};
    for (uint32 j = 0; j < mod; ++j) {
      next[j] = p * j % mod;
    }
    for (uint32 i = 1, w = v / p; i <= w; i += delta) if (!mark[i]) {
      uint32 d = i * p;
      for (uint32 j = 0; j < mod; ++j) {
        lsum[i][next[j]] -= lsum[d][j] - psum[j];
      }
    }
    if (n / p < std::numeric_limits<uint32>::max()) {
      uint32 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        uint32 d = m / i;
        for (uint32 j = 0; j < mod; ++j) {
          lsum[i][next[j]] -= ssum[d][j] - psum[j];
        }
      }
    } else {
      uint64 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) if (!mark[i]) {
        uint32 d = m / i;
        for (uint32 j = 0; j < mod; ++j) {
          lsum[i][next[j]] -= ssum[d][j] - psum[j];
        }
      }
    }
    for (uint64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (uint32 i = v; i >= q; --i) {
      uint32 d = i / p;
      for (uint32 j = 0; j < mod; ++j) {
        ssum[i][next[j]] -= ssum[d][j] - psum[j];
      }
    }
  }
  for (uint32 i = 0; i < mod; ++i) {
    printf("%llu\n", lsum[1][i]);
  }
}

int main() {
  sieve();
  uint64 n, m;
  scanf("%llu%llu", &n, &m);
  prime_count(n, m);
  return 0;
}

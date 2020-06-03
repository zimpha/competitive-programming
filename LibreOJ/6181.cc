#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

using uint32 = unsigned int;
using uint64 = unsigned long long;
using int64 = long long;

const int mod = 998244353;

uint64 squarefree(uint64 n) {
  const uint32 v = static_cast<uint32>(sqrtl(n));
  std::vector<int> mu(v + 1, 0);
  for (int i = 1; i <= v; ++i) {
    mu[i] += i == 1;
    for (int j = i + i; j <= v; j += i) {
      mu[j] -= mu[i];
    }
  }
  uint64 ret = 0;
  for (int i = 1; i <= v; ++i) {
    ret += mu[i] * (n / i / i);
  }
  return ret;
}

int64 count(uint64 n) {
  const uint32 v = static_cast<uint32>(sqrtl(n));
  std::vector<uint64> scnt(v + 1), lcnt(v + 1);
  for (uint32 i = 1; i <= v; ++i) {
    scnt[i] = i - 1;
    lcnt[i] = n / i - 1;
  }
  for (uint32 p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    const uint64 pcnt = scnt[p - 1];
    const uint64 q = (uint64)p * p;
    const uint32 ed = std::min<uint64>(v, n / q);
    for (uint32 i = 1, w = v / p; i <= w; ++i) {
      const uint32 d = i * p;
      lcnt[i] -= lcnt[d] - pcnt;
    }
    if (n / p < std::numeric_limits<int>::max()) {
      const uint32 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) {
        uint32 d = m / i;
        lcnt[i] -= scnt[d] - pcnt;
      }
    } else {
      const uint64 m = n / p;
      for (uint32 i = v / p + 1; i <= ed; ++i) {
        uint32 d = m / i;
        lcnt[i] -= scnt[d] - pcnt;
      }
    }
    for (uint32 i = v; i >= q; --i) {
      const uint32 d = i / p;
      scnt[i] -= scnt[d] - pcnt;
    }
  }
  return lcnt[1];
}

int main() {
  uint64 n;
  scanf("%llu", &n);
  auto ret = (int64)(squarefree(n) - count(n) * 2) % mod;
  if (ret < 0) ret += mod;
  printf("%lld\n", ret);
  return 0;
}

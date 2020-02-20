#include <cmath>
#include <numeric>
#include <cassert>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

using uint64 = unsigned long long;
using int64 = long long;
using uint32 = unsigned int;
using pii = std::pair<uint64, uint32>;

inline uint64 sqr(uint64 x) { return x * x; }
inline uint64 isqrt(uint64 x) { return sqrtl(x); }
inline uint32 ctz(uint64 x) { return __builtin_ctzll(x); }

template <typename T>
T gcd(T a, T b) {
  return b ? gcd(b, a % b) : a;
}

int64 lcm(int64 a, int64 b, int64 n) {
  int64 r = b;
  for (int64 i = a; i < b; ++i) {
    if (n % i != 0) return n + 1;
    int64 g = gcd(r, i);
    r /= g;
    if (r <= n / i) r *= i;
    else return n + 1;
  }
  return r;
}

std::pair<int64, int64> solve2(int64 n) {
  int64 x = isqrt(n);
  while (x * (x + 1) >= n) --x;
  while (x * (x + 1) < n) ++x;
  std::pair<int64, int64> ret{n, n};
  if (x * (x + 1) == n) return {x, x + 1};
  else return {n, n};
}

std::pair<int64, int64> solve3(int64 n) {
  for (auto m : std::vector<int>{1, 2}) {
    auto x = cbrtl(n * m);
    while (x * (x + 1) * (x + 2) >= n * m) --x;
    while (x * (x + 1) * (x + 2) < n * m) ++x;
    if (lcm(x, x + 2, n) == n) return {x, x + 2};
  }
  return {n, n};
}

std::pair<int64, int64> solve4(uint64 n) {
  for (auto m : std::vector<int>{1, 2, 3, 6}) {
    auto x = isqrt(isqrt(n * m));
    while (x * (x + 1) * (x + 2) * (x + 3) >= n * m) --x;
    while (x * (x + 1) * (x + 2) * (x + 3) < n * m) ++x;
    if (lcm(x, x + 3, n) == n) return {x, x + 3};
  }
  return {n, n};
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n;
    scanf("%lld", &n);
    auto ret = solve2(n);
    ret = std::min(solve3(n), ret);
    ret = std::min(solve4(n), ret);
    int bound = pow(n, 0.2) * pow(2 * 3 * 5 * 7 * 11, 0.2);
    for (int a = 1; a <= bound; ++a) if (n % a == 0) {
      for (int b = a + 4; b <= a + 50; ++b) if (n % b == 0) {
        auto u = lcm(a, b, n);
        if (u > n) break;
        if (u == n) ret = std::min(ret, {a, b});
      }
    }
    if (ret.first == n) puts("NIE");
    else printf("%lld %lld\n", ret.first, ret.second);
  }
  return 0;
}

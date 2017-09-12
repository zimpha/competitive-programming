#include <cstdio>
#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <stack>

const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 0};

const int mod = 1e9 + 7;

using int64 = long long;
using int128 = __int128;

int64 pow_mod(int64 a, int64 n, int64 m) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

int64 D(int m, int64 n) {
  int64 sq = sqrt(n);
  std::vector<int64> small_sum(sq + 1), large_sum(sq + 1);
  for (int i = 1; i <= sq; ++i) {
    for (int j = i; j <= sq; j += i) {
      small_sum[j] += 1;
    }
    small_sum[i] += small_sum[i - 1];
  }

  auto get = [&](int64 g) {
    int64 s = n / g;
    if (s <= sq) return small_sum[s];
    s = n / s;
    if (large_sum[s]) return large_sum[s];
    int64 &ret = large_sum[s];
    s = n / g;
    int64 v = sqrt(s);
    for (int64 i = 1; i <= v; ++i) {
      ret += s / i;
    }
    ret = ret + ret - v * v;
    return ret % mod;
  };

  std::vector<int> cnt(46);
  for (int i = 0; p[i]; ++i) {
    for (int x = p[i]; x <= m; x *= p[i]) {
      cnt[i] += m / x;
    }
  }
  int64 d3 = 1, mu = 1, mx = 0;
  for (auto &&x: cnt) {
    if (x) d3 = d3 * (x + 1) * (x + 2) / 2 % mod;
    mx = std::max<int64>(mx, x + 1);
  }
  std::vector<int64> inv(mx + 1);
  for (int i = 1; i <= mx; ++i) {
    inv[i] = pow_mod(i * (i + 1) / 2, mod - 2, mod);
  }

  std::function<int64(int, int64, int64)> rec = [&] (int d, int64 g, int64 upp) {
    //printf("%lld %lld %lld %lld\n", g, mu, get(g), d3);
    int64 ret = mu * get(g) % mod * d3 % mod;
    for (int i = d; p[i]; ++i) {
      if (upp < p[i] || p[i] > m) break;
      d3 = d3 * inv[cnt[i] + 1] % mod;
      d3 = d3 * (cnt[i] * (cnt[i] + 1) / 2) % mod;
      mu *= -1;
      ret += rec(i + 1, g * p[i], upp / p[i]);
      mu *= -1;
      d3 = d3 * inv[cnt[i]] % mod;
      d3 = d3 * ((cnt[i] + 1) * (cnt[i] + 2) / 2) % mod;
    }
    return ret % mod;
  };
  return (rec(0, 1, n) + mod) % mod;
}

int main() {
  std::cout << D(3, 100) << std::endl;
  std::cout << D(4, 1000000) << std::endl;
  std::cout << D(200, 1000000000000ll) << std::endl;
  return 0;
}

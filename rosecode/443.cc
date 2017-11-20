#include <vector>
#include <iostream>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 S(int n) {
  std::vector<int> cnt(n * 2 + 1);
  int64 ret = 0, now = 1, sq = 1;
  auto add = [&](int p) {
    cnt[p]++;
    now = now * p % mod;
    if (cnt[p] == 1) sq = sq * p % mod;
  };
  auto del = [&](int p) {
    cnt[p]--;
    now = now * pow_mod(p, mod - 2) % mod;
    if (cnt[p] == 0) sq = sq * pow_mod(p, mod - 2) % mod;
  };
  for (int i = 1; i <= n; ++i) {
    add(2);
    int x = 2 * i - 1;
    for (int d = 2; d * d <= x; ++d) {
      while (x % d == 0) {
        add(d);
        x /= d;
      }
    }
    if (x > 1) add(x);
    x = i;
    for (int d = 2; d * d <= x; ++d) {
      while (x % d == 0) {
        del(d);
        x /= d;
      }
    }
    if (x > 1) del(x);
    ret += now * pow_mod(sq, mod - 2) % mod;
    ret %= mod;
  }
  return ret;
}

int main() {
  // \binom{2n, n}
  // a_n = 2n! / n! / n!
  std::cout << S(10) << std::endl;
  std::cout << S(100) << std::endl;
  std::cout << S(1000) << std::endl;
  std::cout << S(1000000) << std::endl;
  return 0;
}

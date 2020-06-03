#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using int64 = long long;

const int mod = 20190601;

int64 S(int64 n) {
  const int v = static_cast<int>(sqrtl(n));
  std::vector<int64> ssum(v + 1), lsum(v + 1);
  std::vector<int64> scnt(v + 1), lcnt(v + 1);
  std::vector<bool> mark(v + 1);
  auto sum = [&](int64 n) {
    int64 x = n, y = n + 1;
    if (x & 1) y >>= 1;
    else x >>= 1;
    return x % mod * y % mod;
  };
  for (int i = 1; i <= v; ++i) {
    ssum[i] = sum(i) - 1;
    scnt[i] = i - 1;
    lsum[i] = sum(n / i) - 1;
    lcnt[i] = n / i - 1;
  }
  int64 ret = 0;
  for (int p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    int psum = ssum[p - 1] % mod, pcnt = scnt[p - 1];
    int64 q = (int64)p * p;
    int ed = std::min<int64>(v, n / q);
    ret += (lcnt[p] - pcnt) * (p - 1) % mod;
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= (lsum[d] - psum + mod) * p % mod;
        if (lsum[i] < 0) lsum[i] += mod;
        lcnt[i] -= lcnt[d] - pcnt;
      } else {
        lsum[i] -= (ssum[n / d] - psum + mod) * p % mod;
        if (lsum[i] < 0) lsum[i] += mod;
        lcnt[i] -= scnt[n / d] - pcnt;
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int i = v; i >= q; --i) {
      ssum[i] -= (ssum[i / p] - psum) * p;
      scnt[i] -= scnt[i / p] - pcnt;
    }
  }
  ret %= mod;
  ret = (ret + mod * 3 - lcnt[1] % mod * 2 + lsum[1]) % mod;
  return ret;
}

int main() {
  int64 n;
  std::cin >> n;
  std::cout << S(n) << std::endl;
  return 0;
}

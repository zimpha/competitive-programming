#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using int64 = long long;
using int128 = __int128;

const int mod = 1e9;

inline int64 sub_mod(int64 x, int64 y) {
  return (x - y + mod) % mod;
}

int64 S(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int64> ssum(v + 1), lsum(v + 1);
  std::vector<int64> scnt(v + 1), lcnt(v + 1);
  std::vector<bool> mark(v + 1);
  auto sum = [&](int128 n) {
    return n * (n + 1) / 2 % mod;
  };
  for (int64 i = 1; i <= v; ++i) {
    ssum[i] = sum(i) - 1;
    scnt[i] = i - 1;
    lsum[i] = sum(n / i) - 1;
    lcnt[i] = n / i - 1;
  }
  int64 ret = 0;
  for (int64 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    int64 psum = ssum[p - 1], pcnt = scnt[p - 1];
    int64 q = p * p, ed = std::min(v, n / q);
    ret += (lcnt[p] - pcnt) * p % mod;
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] = sub_mod(lsum[i], sub_mod(lsum[d], psum) * p % mod);
        lcnt[i] -= lcnt[d] - pcnt;
      } else {
        lsum[i] = sub_mod(lsum[i], sub_mod(ssum[n / d], psum) * p % mod);
        lcnt[i] -= scnt[n / d] - pcnt;
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int64 i = v; i >= q; --i) {
      ssum[i] = sub_mod(ssum[i], sub_mod(ssum[i / p], psum) * p % mod);
      scnt[i] -= scnt[i / p] - pcnt;
    }
  }
  return (ret + lsum[1]) % mod;
}

int main() {
  std::cout << S(100) << std::endl;
  std::cout << S(1000000000000ll) << std::endl;
  return 0;
}

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using int64 = unsigned long long;
using int128 = __int128;

int64 S(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int64> ssum(v + 1), lsum(v + 1);
  std::vector<int64> scnt(v + 1), lcnt(v + 1);
  std::vector<bool> mark(v + 1);
  auto sum = [&](int64 n) {
    int64 x = n, y = n + 1;
    if (x & 1) y >>= 1;
    else x >>= 1;
    return x * y;
  };
  for (int64 i = 1; i <= v; ++i) {
    ssum[i] = sum(i) - 1;
    scnt[i] = i - 1;
    lsum[i] = sum(n / i) - 1;
    lcnt[i] = n / i - 1;
  }
  int64 ret = 0;
  for (int64 p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    int64 psum = ssum[p - 1], pcnt = scnt[p - 1];
    int64 q = p * p, ed = std::min(v, n / q);
    ret += (lcnt[p] - pcnt) * p;
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= (lsum[d] - psum) * p;
        lcnt[i] -= lcnt[d] - pcnt;
      } else {
        lsum[i] -= (ssum[n / d] - psum) * p;
        lcnt[i] -= scnt[n / d] - pcnt;
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int64 i = v; i >= q; --i) {
      ssum[i] -= (ssum[i / p] - psum) * p;
      scnt[i] -= scnt[i / p] - pcnt;
    }
  }
  return ret + lsum[1];
}

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int64 n;
    std::cin >> n;
    std::cout << S(n) << std::endl;
  }
  return 0;
}

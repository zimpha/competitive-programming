#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
#include <iomanip>

using int64 = long long;
using int128 = __int128;

std::ostream& operator << (std::ostream &os, const int128 &v) {
  const int64 base = 1000000000000000000ll;
  if (v < base) os << int64(v);
  else os << int64(v / base) << std::setw(18) << std::setfill('0') << int64(v % base);
  return os;
}

int128 F(int64 n) {
  const int64 sn = static_cast<int64>(sqrt(n));
  std::vector<int64> pl;
  std::vector<bool> mark(sn + 1);
  for (int i = 2; i <= sn; ++i) if (!mark[i]) {
    pl.push_back(i);
    for (int j = i + i; j <= sn; j += i) mark[j] = 1;
  }

  auto sieve = [&] () {
    std::vector<int> f(sn + 1, 1);
    for (auto &&x: pl) f[x] = x % 4 == 3 ? 0 : x;
    for (int i = 2; i <= sn; ++i) {
      for (int j = 0, u = sn / i; j < pl.size() && pl[j] <= u; ++j) {
        int v = i * pl[j];
        if (i % pl[j]) f[v] = f[i] * (pl[j] % 4 == 3 ? 0 : pl[j]);
        else {
          f[v] = 0;
          break;
        }
      }
    }
    return f;
  };

  auto calc_G = [&]() {
    static const int N = 1e6 + 10;
    static int128 ssum[N][2], lsum[N][2];
    auto sum = [](int64 n, int e) {
      if (n < e) return int128(0);
      int128 k = (n - e) / 4;
      return e * (k + 1) + 4 * k * (k + 1) / 2;
    };
    for (int64 i = 1; i <= sn; ++i) {
      ssum[i][0] = sum(i, 1) - 1;
      ssum[i][1] = sum(i, 3);
      lsum[i][0] = sum(n / i, 1) - 1;
      lsum[i][1] = sum(n / i, 3);
    }
    for (auto &&p: pl) if (p <= sn && p != 2) {
      int64 q = p * p, ed = std::min(sn, n / q);
      int m = p % 4 / 2;
      for (int64 i = 1; i <= ed; ++i) {
        int64 d = i * p;
        if (d <= sn) {
          lsum[i][m] -= (lsum[d][0] - ssum[p - 1][0]) * p;
          lsum[i][m ^ 1] -= (lsum[d][1] - ssum[p - 1][1]) * p;
        } else {
          lsum[i][m] -= (ssum[n / d][0] - ssum[p - 1][0]) * p;
          lsum[i][m ^ 1] -= (ssum[n / d][1] - ssum[p - 1][1]) * p;
        }
      }
      for (int64 i = sn; i >= q; --i) {
        ssum[i][(p % 4 / 2)] -= (ssum[i / p][0] - ssum[p - 1][0]) * p;
        ssum[i][(p % 4 / 2) ^ 1] -= (ssum[i / p][1] - ssum[p - 1][1]) * p;
      }
    }
    std::vector<int128> ls(sn + 1);
    for (int i = 1; i <= sn; ++i) {
      ls[i] = lsum[i][0] - ssum[sn][0];
    }
    return ls;
  };

  auto calc_F = [&](const std::vector<int64> &sf) {
    std::vector<int64> val(sn * 2);
    std::vector<int128> sum(sn * 2, 1);
    for (int i = 1; i <= sn; ++i) val[i - 1] = i;
    for (int i = sn; i >= 1; --i) val[sn - i + sn] = n / i;
    int ip = 0;
    for (auto &&v: val) {
      while (ip < pl.size() && pl[ip] <= v / pl[ip]) ++ip;
      v = ip - 1;
    }
    for (int i = pl.size() - 1; i >= 0; --i) if (pl[i] % 4 != 3) {
      for (int j = sn * 2 - 1; j >= 0; --j) {
        if (val[j] < i) break;
        int64 x = (j < sn ? j + 1 : n / (sn * 2 - j)) / pl[i];
        if (x) {
          int k = x <= sn ? x - 1 : 2 * sn - n / x;
          int l = pl[std::max<int64>(i, val[k])], r = std::min<int64>(x, sn);
          sum[j] += (sum[k] + (l < r ? sf[r] - sf[l] : 0)) * pl[i];
        }
      }
    }
    return sum.back();
  };

  std::vector<int64> sf(sn + 1);
  std::vector<int> f = sieve();
  for (auto &&x: pl) sf[x] = f[x];
  for (int i = 1; i <= sn; ++i) {
    sf[i] = sf[i - 1] + sf[i];
  }
  std::vector<int128> G = calc_G();
  int128 ret = 0;
  for (int i = 1; i <= sn; ++i) {
    ret += f[i] * G[i];
  }
  ret += calc_F(sf);
  return ret - 1;
}

int main() {
  std::cout << F(10) << std::endl;
  std::cout << F(1000) << std::endl;
  std::cout << F(1000000) << std::endl;
  std::cout << F(1000000000000ll) << std::endl;
  return 0;
}

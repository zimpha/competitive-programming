#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>

using int64 = long long;
using int128 = __int128;

std::ostream& operator << (std::ostream &os, const int128 &v) {
  const int64 base = 1000000000000000000ll;
  if (v < base) os << int64(v);
  else os << int64(v / base) << std::setw(18) << std::setfill('0') << int64(v % base);
  return os;
}

int128 S(int64 n) {
  int64 sn = sqrt(n);
  std::vector<bool> mark(sn + 1);
  std::vector<int64> pl;
  for (int i = 2; i <= sn; ++i) if (!mark[i]) {
    pl.push_back(i);
    for (int j = i; j <= sn; j += i) mark[j] = 1;
  }
  auto prime_count = [&pl] (int64 n) {
    static const int N = 1e6 + 10;
    const int64 v = static_cast<int64>(sqrt(n));
    static int128 ssum[N][2], lsum[N][2];
    auto sum = [](int64 n, int e) {
      if (n < e) return int128(0);
      int128 k = (n - e) / 4;
      return e * (k + 1) + 4 * k * (k + 1) / 2;
    };
    for (int64 i = 1; i <= v; ++i) {
      ssum[i][0] = sum(i, 1) - 1;
      ssum[i][1] = sum(i, 3);
      lsum[i][0] = sum(n / i, 1) - 1;
      lsum[i][1] = sum(n / i, 3);
    }
    for (auto &&p: pl) if (p <= v && p != 2) {
      int64 q = p * p, ed = std::min(v, n / q);
      int m = p % 4 / 2;
      for (int64 i = 1; i <= ed; ++i) {
        int64 d = i * p;
        if (d <= v) {
          lsum[i][m] -= (lsum[d][0] - ssum[p - 1][0]) * p;
          lsum[i][m ^ 1] -= (lsum[d][1] - ssum[p - 1][1]) * p;
        } else {
          lsum[i][m] -= (ssum[n / d][0] - ssum[p - 1][0]) * p;
          lsum[i][m ^ 1] -= (ssum[n / d][1] - ssum[p - 1][1]) * p;
        }
      }
      for (int64 i = v; i >= q; --i) {
        ssum[i][(p % 4 / 2)] -= (ssum[i / p][0] - ssum[p - 1][0]) * p;
        ssum[i][(p % 4 / 2) ^ 1] -= (ssum[i / p][1] - ssum[p - 1][1]) * p;
      }
    }
    std::vector<int128> ls(v + 1);
    for (int i = 1; i <= v; ++i) {
      ls[i] = lsum[i][0] - ssum[v][0];
    }
    return ls;
  };

  auto sum = prime_count(n);
  int m = 0;
  for (auto &&p: pl) {
    if (p % 4 == 1) pl[m++] = p;
  }
  pl.resize(m);
  std::function<int128(int, int64, int64)> dfs = [&](int d, int64 now, int64 upp) {
    int128 ret = now;
    if (now <= sn) {
      ret += now * sum[now];
    }
    if (upp >= 2) {
      ret += now * 2;
      if (now * 2 <= sn) {
        ret += now * 2 * sum[now * 2];
      }
    }
    for (int i = d; i < m; ++i) {
      if (pl[i] <= upp) {
        ret += dfs(i + 1, now * pl[i], upp / pl[i]);
      } else break;
    }
    return ret;
  };
  return dfs(0, 1, n) - 1;
}

int main() {
  std::cout << S(10) << std::endl;
  std::cout << S(1000) << std::endl;
  std::cout << S(1000000) << std::endl;
  std::cout << S(1000000000000) << std::endl;
  return 0;
}

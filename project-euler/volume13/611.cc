#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <functional>
#include <map>

using int64 = long long;

const int N = 1e6 + 10;

std::vector<int> fac[N];
int p[N], dvs[N], pc;

void sieve() {
  for (int i = 1; i < N; ++i) dvs[i] = 1;
  for (int i = 2; i < N; ++i) if (!p[i]) {
    p[pc++] = i;
    for  (int j = i; j < N; j += i) {
      p[j] = 1;
      fac[j].push_back(i);
      int c = 0;
      for (int x = j; x % i == 0; x /= i) ++c;
      dvs[j] *= c * 2 + 1;
    }
  }
}

std::pair<std::vector<int64>, std::vector<int64>> prime_count(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  static int64 ssum[N][2], lsum[N][2];
  auto sum = [](int64 n, int e) {
    if (n < e) return int64(0);
    return (n - e) / 4 + 1;
  };
  for (int64 i = 1; i <= v; ++i) {
    ssum[i][0] = sum(i, 1) - 1;
    ssum[i][1] = sum(i, 3);
    lsum[i][0] = sum(n / i, 1) - 1;
    lsum[i][1] = sum(n / i, 3);
  }
  for (int it = 1; it < pc && ::p[it] <= v; ++it) {
    int64 p = ::p[it], q = p * p, ed = std::min(v, n / q);
    int m = p % 4 / 2;
    for (int i = 1; i <= ed; ++i) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i][m] -= lsum[d][0] - ssum[p - 1][0];
        lsum[i][m ^ 1] -= lsum[d][1] - ssum[p - 1][1];
      } else {
        lsum[i][m] -= ssum[n / d][0] - ssum[p - 1][0];
        lsum[i][m ^ 1] -= ssum[n / d][1] - ssum[p - 1][1];
      }
    }
    for (int64 i = v; i >= q; --i) {
      ssum[i][(p % 4 / 2)] -= ssum[i / p][0] - ssum[p - 1][0];
      ssum[i][(p % 4 / 2) ^ 1] -= ssum[i / p][1] - ssum[p - 1][1];
    }
  }
  std::vector<int64> ss(v + 1), ls(v + 1);
  for (int i = 1; i <= v; ++i) {
    ss[i] = ssum[i][0];
    ls[i] = lsum[i][0];
  }
  return {std::move(ss), std::move(ls)};
}

int64 solve(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int> n1, n3;
  for (int i = 1; i <= v; ++i) {
    bool flag1 = true, flag3 = true;
    for (auto &&p: fac[i]) {
      if (p % 4 != 1) flag1 = false;
      if (p % 4 != 3) flag3 = false;
    }
    if (flag1 && dvs[i] % 2 == 1) n1.push_back(i);
    if (flag3) n3.push_back(i);
  }
  std::vector<int64> ssum, lsum;
  std::tie(ssum, lsum) = prime_count(n);
  auto count = [&] (int64 u) {
    int64 ret = u <= v ? ssum[u] : lsum[n / u];
    for (int t = 5; ; t += 4) {
      int64 x = pow(u, 1.0 / t);
      if (x < 5) break;
      ret += ssum[x];
    }
    return ret;
  };
  int64 ret = 0;
  std::map<std::pair<int, int>, int> mp;
  for (auto &&x: n3) {
    int64 u = n / x / x;
    for (auto &&y: n1) {
      if ((int64)y * y > u) break;
      int64 uu = u / y / y;
      int64 cnt = 0;
      for (int64 e = 1; e <= uu; e *= 2) {
        ret += count(uu / e);
        cnt += count(uu / e);
        for (auto &&p: fac[y]) if (p <= uu / e) {
          int64 pp = p, c = 1;
          while (pp <= uu / e / p) pp *= p, ++c;
          ret -= (c - 1) / 4 + 1;
          cnt -= (c-  1) / 4 + 1;
        }
      }
      if (dvs[y] % 4 == 1) {
        for (int64 p = 2; p <= uu; p *= 4) ++ret, ++cnt;
      } else {
        for (int64 p = 1; p <= uu; p *= 4) ++ret, ++cnt;
      }
      mp[{x * x, y * y}] = cnt;
    }
  }
  auto parity = [](int64 x) {
    int b = 1, a = 1;
    for (int64 i = 2; i * i <= x; ++i) if (x % i == 0) {
      int e = 0;
      while (x % i == 0) x /= i, ++e;
      if (i % 4 == 3) continue;
      if (i % 4 == 1) b *= e * 2 + 1;
    }
    if (x > 1 && x % 4 == 1) b *= 3;
    b -= (a % 2) ? -1 : 1;
    return b >> 1 & 1;
  };
  for (int64 i = 1; i * i * 2 <= n; ++i) {
    int cnt = 0;
    if (parity(i)) --ret, cnt = -1;
    else ++ret, cnt = 1;
    int u = 1, v = 1, x = i;
    for (int d = 2; d * d <= x; ++d) if (x % d == 0) {
      int e = 0;
      while (x % d == 0) ++e, x /= d;
      while (e--) {
        if (d % 4 == 3) u *= d * d;
        if (d % 4 == 1) v *= d * d;
      }
    }
    if (x > 1) {
      if (x % 4 == 3) u *= x * x;
      if (x % 4 == 1) v *= x * x;
    }
    mp[{u, v}] += cnt;
  }
  return ret;
}

int main() {
  sieve();
  std::cout << solve(100) << std::endl;
  std::cout << solve(1000) << std::endl;
  std::cout << solve(1000000) << std::endl;
  std::cout << solve(1000000000000ll) << std::endl;
  return 0;
}

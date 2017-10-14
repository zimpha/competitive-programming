#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

using int64 = long long;
using int128 = __int128;

const int mod = 1e9 + 7;

inline int64 sub_mod(int64 x, int64 y) {
  x -= y;
  if (x < 0) x += mod;
  return x;
}

int main() {
  int64 n;
  scanf("%lld", &n);
  const int s = static_cast<int64>(sqrt(n));

  auto sieve = [] (int n) {
    std::vector<int> p;
    std::vector<bool> mark(n + 1);
    std::vector<int> f(n + 1, 1), e(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
      if (!mark[i]) {
        p.push_back(i);
        f[i] = i ^ 1;
        e[i] = 1;
      }
      for (int j = 0, u = n / i; j < p.size() && p[j] <= u; ++j) {
        int v = i * p[j];
        mark[v] = 1;
        if (i % p[j]) {
          f[v] = f[i] * (p[j] ^ 1);
          e[v] = 1;
        } else {
          e[v] = e[i] + 1;
          if (p[j] ^ e[i]) f[v] = f[i] / (p[j] ^ e[i]) * (p[j] ^ e[v]);
          else f[v] = f[i / p[j]] / (p[j] ^ (e[i] - 1)) * (p[j] ^ e[v]);
          break;
        }
      }
    }
    return std::make_pair(std::move(p), std::move(f));
  };

  auto calc_G = [&s](int64 n) {
    std::vector<int64> ssum(s + 1), lsum(s + 1);
    std::vector<int64> scnt(s + 1), lcnt(s + 1);
    std::vector<bool> mark(s + 1);
    for (int i = 1; i <= s; ++i) {
      ssum[i] = (int64)i * (i + 1) / 2 % mod - 1;
      lsum[i] = int128(n / i) * (n / i + 1) / 2 % mod - 1;
      scnt[i] = i - 1;
      lcnt[i] = n / i - 1;
    }
    for (int64 p = 2; p <= s; ++p) {
      if (scnt[p] == scnt[p - 1]) continue;
      int64 psum = ssum[p - 1], pcnt = scnt[p - 1];
      int64 q = p * p, ed = std::min<int64>(s, n / q);
      for (int i = 1; i <= ed; ++i) {
        int64 d = i * p;
        if (d <= s) {
          lsum[i] = sub_mod(lsum[i], sub_mod(lsum[d], psum) * p % mod);
          lcnt[i] -= lcnt[d] - pcnt;
        } else {
          lsum[i] = sub_mod(lsum[i], sub_mod(ssum[n / d], psum) * p % mod);
          lcnt[i] -= scnt[n / d] - pcnt;
        }
      }
      for (int64 i = s; i >= q; --i) {
        ssum[i] = sub_mod(ssum[i], sub_mod(ssum[i / p], psum) * p % mod);
        scnt[i] -= scnt[i / p] - pcnt;
      }
    }
    for (int i = 1; i <= s; ++i) {
      ssum[i] = sub_mod(ssum[i], scnt[i]);
      lsum[i] = sub_mod(lsum[i], lcnt[i] % mod);
      if (i >= 2) ssum[i] += 2;
      if (n / i >= 2) lsum[i] += 2;
    }
    for (int i = 1; i <= s; ++i) {
      lsum[i] = sub_mod(lsum[i], ssum[s]);
    }
    return std::move(lsum);
  };

  auto calc_F = [&s](int64 n, const std::vector<int> &p, const std::vector<int> &sf) {
    std::vector<int64> val(s * 2), sum(s * 2, 1);
    for (int i = 1; i <= s; ++i) val[i - 1] = i;
    for (int i = s; i >= 1; --i) val[s - i + s] = n / i;
    int ip = 0;
    for (auto &&v: val) {
      while (ip < p.size() && p[ip] <= v / p[ip]) ++ip;
      v = ip - 1;
    }
    for (int i = p.size() - 1; i >= 0; --i) {
      for (int j = s * 2 - 1; j >= 0; --j) {
        if (val[j] < i) break;
        int64 x = (j < s ? j + 1 : n / (s * 2 - j)) / p[i];
        for (int c = 1; x; ++c, x /= p[i]) {
          int k = x <= s ? x - 1 : 2 * s - n / x;
          int l = p[std::max<int64>(i, val[k])], r = std::min<int64>(x, s);
          sum[j] += (sum[k] + (l < r ? sf[r] - sf[l] : 0)) * (p[i] ^ c) % mod;
        }
        sum[j] %= mod;
      }
    }
    return sum.back();
  };

  std::vector<int> p, f, sf(s + 1);
  std::tie(p, f) = sieve(s);
  for (auto &&x: p) sf[x] = f[x];
  for (int i = 1; i <= s; ++i) {
    sf[i] = (sf[i - 1] + sf[i]) % mod;
  }
  std::vector<int64> G = calc_G(n);
  int64 ret = 0;
  for (int i = 1; i <= s; ++i) {
    ret += f[i] * G[i] % mod;
  }
  ret += calc_F(n, p, sf);
  printf("%lld\n", ret % mod);
  return 0;
}

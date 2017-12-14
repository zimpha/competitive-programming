#include <cstdio>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

const int mod = 1e9 + 7;

using int64 = long long;
using int128 = __int128;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 sum(int64 a, int64 q, int64 n) {
  if (q == 1) return a * n % mod;
  int64 iv = pow_mod(q - 1, mod - 2);
  return iv * a % mod * (pow_mod(q, n) + mod - 1) % mod;
}

int64 S(int n, int64 k) {
  int m = n * (log(n) + 5);
  std::vector<bool> mark(m);
  std::vector<int> p;
  for (int i = 2; i < m; ++i) {
    if (!mark[i]) p.push_back(i);
    for (int j = 0; j < p.size() && p[j] * i < m; ++j) {
      mark[p[j] * i] = true;
      if (i % p[j] == 0) break;
    }
  }
  std::vector<char> s;
  for (int i = 0; i < n; ++i) {
    std::string t = std::to_string(p[i]);
    for (auto &&c: t) s.push_back(c);
  }
  std::reverse(s.begin(), s.end());
  n = s.size();
  int64 pn = pow_mod(10, n), pnk = pow_mod(pn, k);
  int64 pw = 1, k2 = (int128)k * (k + 1) / 2 % mod * n % mod;
  int64 iv = pow_mod(pn - 1, mod - 2);
  int64 s1 = 10 * n * iv % mod * ((pnk - k + (pnk - pn) * iv) % mod) % mod;
  int64 s2 = 10 * iv % mod * (pnk - 1) % mod;
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    int o = s[i] - '0';
    ret -= k2 * o;
    ret += k % mod * i * o % mod;
    ret += o * pw * s1 % mod;
    ret -= o * i * pw % mod * s2 % mod;
    pw = pw * 10 % mod;
  }
  ret %= mod;
  ret = ret * pow_mod(9, mod - 2) % mod;
  return (ret + mod) % mod;
}

int main() {
  std::cout << S(1e6, 1e12) << std::endl;
  return 0;
}

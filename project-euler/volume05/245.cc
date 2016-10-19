#include <bits/stdc++.h>

using LL = long long;

std::vector<int> pl;
LL upp;

inline LL mul_mod(LL a, LL b, LL mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  LL k = (LL)((long double)a * b / mod);
  LL res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

LL pow_mod_LL(LL a, LL n, LL m) {
  LL res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(LL n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (~n & 1) return false;
  const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
  LL e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
  while (~e & 1) e >>= 1, ++c;
  for (int i = 0; u[i]; ++i) {
    if (n <= u[i]) return true;
    a = pow_mod_LL(u[i], e, n);
    if (a == 1) continue;
    for (int j = 1; a != n - 1; ++j) {
      if (j == c) return false;
      a = mul_mod(a, a, n);
    }
  }
  return true;
}

LL dfs(LL n, LL phi, int last) {
  LL ret = 0, p = pl[last];
  LL d = n - phi, k = (n * p - 1) / (p * d + phi) + 1;
  k += k & 1;
  LL x = k * phi + 1, y = n - k * d;
  while (y > 0) {
    p = x / y;
    if (n * p > upp) break;
    if (x % y == 0 && is_prime(p)) {
      assert((n * p - 1) % (n * p - phi * (p - 1)) == 0);
      std::cout << n * p << std::endl;
      ret += n * p;
    }
    x += phi * 2, y -= d * 2;
  }
  for (size_t i = last + 1; i < pl.size(); ++i) {
    p = pl[i];
    if (n * p * p > upp) break;
    ret += dfs(n * p, phi * (p - 1), i);
  }
  return ret;
}

LL run(LL n) {
  upp = n;
  int m = sqrt(n) + 10;
  std::vector<bool> vis(m, 0);
  for (int i = 2; i < m; ++i) if (!vis[i]) {
    if (i != 2) pl.push_back(i);
    for (int j = i; j < m; j += i) vis[j] = 1;
  }
  LL ret = 0;
  for (size_t i = 0; i < pl.size(); ++i) {
    LL p = pl[i];
    ret += dfs(p, p - 1, i);
  }
  return ret;
}

int main() {
  std::cout << run(200000000000ll) << std::endl;
  return 0;
}

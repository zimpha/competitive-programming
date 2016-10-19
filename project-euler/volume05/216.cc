#include <bits/stdc++.h>

using LL = long long;

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
  const int u[] = {2,325,9375,28178,450775,9780504,1795265022,0};
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

int run(int n) {
  int ret = 0;
  for (int i = 2; i <= n; ++i) {
    if (is_prime(2ll * i * i - 1)) ++ret;
  }
  return ret;
}

int main() {
  std::cout << run(10000) << std::endl;
  std::cout << run(50000000) << std::endl;
  return 0;
}

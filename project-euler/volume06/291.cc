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


// p = n^2 + (n + 1)^2
int run(LL lim) {
  int ret = 0;
  for (int n = 1; ; ++n) {
    LL p = 1ll * n * n + 1ll * (n + 1) * (n + 1);
    if (p > lim) break;
    ret += is_prime(p);
  }
  return ret;
}

int main() {
  std::cout << run(5000000000000000ll) << std::endl;
  return 0;
}

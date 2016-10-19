#include <bits/stdc++.h>

using LL = long long;

inline LL add_mod(LL x, LL y, LL m) {
  return (x % m + y) % m;
}

inline LL mul_mod(LL a, LL b, LL mod) {
  if (mod < int(1e9)) return a * b % mod;
  LL k = (LL)((long double)a * b / mod);
  LL res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

LL pow_mod(LL a, LL n, LL m) {
  LL res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

void fib(LL n, LL &x, LL &y, LL m) {// store in x, n-th
  if (n == 1) {
    x = y = 1;
    return;
  } else if (n & 1) {
    fib(n - 1, y, x, m);
    y = add_mod(y, x, m);
  } else {
    LL a, b;
    fib(n >> 1, a, b, m);
    y = add_mod(mul_mod(a, a, m), mul_mod(b, b, m), m);
    x = add_mod(mul_mod(a, b, m), mul_mod(a, b - a + m, m), m);
  }
}

LL calc(LL n, LL x, LL m) {
  // F_n(x) = (f_n*x^(n+2) + f_{n+1}*x^{n+1} - x) / (x^2+x-1)
  if (x == 0) return 0;
  LL mul = x * x + x - 1, u, v;
  m *= mul;
  fib(n, u, v, m);
  LL ret = mul_mod(u, pow_mod(x, n + 2, m), m);
  ret += mul_mod(v, pow_mod(x, n + 1, m), m);
  ret -= x;
  ret %= m;
  ret += m;
  ret %= m;
  return ret / mul;
}

LL run(LL n, int u, LL m) {
  LL ret = 0;
  for (int x = 0; x <= u; ++x) {
    ret += calc(n, x, m);
    ret %= m;
  }
  return ret;
}

int main() {
  std::cout << calc(7, 11, 1307674368000ll) << std::endl;
  std::cout << run(1000000000000000ll, 100, 1307674368000ll) << std::endl;
}

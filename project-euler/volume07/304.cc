#include <bits/stdc++.h>

using LL = long long;

const int N = 20000000;

int p[N], mark[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mark[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

void sieve_interval(LL s, LL n) {
  for (int i = 0; i < n; ++i) mark[i] = 1;
  for (int i = 0; i < m; ++i) {
    LL x = s / p[i] * p[i];
    while (x < s) x += p[i];
    for (; x < s + n; x += p[i]) mark[x - s] = 0;
  }
}

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


LL run(LL s, int n, LL mod = 1234567891011ll) {
  sieve_interval(s, n * 100);
  LL ret = 0, rest = n, x, y;
  for (int i = 0; i < n * 100 && rest; ++i) {
    if (mark[i]) {
      fib(i + s, x, y, mod);
      ret += x;
      --rest;
    }
  }
  std::cout << rest << std::endl;
  return ret % mod;
}

int main() {
  sieve();
  std::cout << run(100000000000000ll, 100000) << std::endl;
}

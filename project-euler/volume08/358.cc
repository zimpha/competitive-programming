#include <bits/stdc++.h>

using LL = long long;

bool is_prime(LL n) {
  for (LL i = 3; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

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


LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = mul_mod(r, a, m);
    a = mul_mod(a, a, m);
  }
  return r;
}

bool is_primitive_root(LL g, LL p) {
  LL n = p - 1;
  std::vector<LL> u;
  for (LL i = 2; i * i <= n; ++i) if (n % i == 0) {
    u.push_back(i);
    while (n % i == 0) n /= i;
  }
  if (n > 1) u.push_back(n);
  for (auto &&a : u) {
    if (pm(g, (p - 1) / a, p) == 1) return false;
  }
  return true;
}

// https://en.wikipedia.org/wiki/Cyclic_number
// m = (10 ** (p - 1) - 1) / p mod 10 ** 5 = 56789
// 99999 = 56789 * p mod 10 ** 5 => p mod 10 ** 5 = 09891
LL run() {
  LL p, b = 10;
  for (int k = 1; ; ++k) {
    p = k * 100000ll + 9891;
    if (is_prime(p) && pm(10, p - 1, p) == 1) {
      LL x = 100000000000ll / p;
      if (x == 137 && is_primitive_root(10, p)) break;
    }
  }
  std::cout << p << std::endl;
  return 9 * (p - 1) / 2;
  LL ret = 0, r = 1;
  do {
    LL x = r * b;
    LL d = x / p;
    r = x % p;
    ret += d;
  } while (r != 1);
  return ret; 
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

#include <cstdio>
#include <iomanip>
#include <iostream>

using int64 = long long;
using int128 = __int128;

std::ostream& operator << (std::ostream &os, const int128 &n) {
  const int64 base = 1000000000000000000ll;
  if (n < base) os << int64(n);
  else os << int64(n / base) << std::setw(18) << std::setfill('0') << int64(n % base);
}

inline int64 mul_mod(int64 a, int64 b, int64 mod) {
  if (mod < int(1e9)) return a * b % mod;
  int64 k = (int64)((long double)a * b / mod);
  int64 res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

int64 pow_mod(int64 a, int64 n, int64 m) {
  int64 res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(int64 n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (~n & 1) return false;
  const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
  int64 e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
  while (~e & 1) e >>= 1, ++c;
  for (int i = 0; u[i]; ++i) {
    if (n <= u[i]) return true;
    a = pow_mod(u[i], e, n);
    if (a == 1) continue;
    for (int j = 1; a != n - 1; ++j) {
      if (j == c) return false;
      a = mul_mod(a, a, n);
    }
  }
  return true;
}

int main() {
  const int d[4] = {2, 3, 5, 7};
  int64 pw[20];
  pw[0] = 1;
  for (int i = 1; i < 20; ++i) pw[i] = pw[i - 1] * 10;
  int64 cnt = 0;
  int128 sum = 0;
  for (int i = 1; i <= 19; i += 2) {
    int len = (i + 1) / 2;
    for (int mask = 0; mask < (1 << i + 1); ++mask) {
      int64 n = 0;
      for (int j = 0; j < len; ++j) {
        int o = d[mask >> (j * 2) & 3];
        n += o * pw[j];
        if (j != len - 1) n += o * pw[i - j - 1];
      }
      if (is_prime(n)) {
        ++cnt;
        sum += n;
      }
    }
  }
  std::cout << cnt << ',' << sum << std::endl;
  return 0;
}

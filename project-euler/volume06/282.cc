#include <bits/stdc++.h>

int phi(int n) {
  int r = n;
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
    r = r / i * (i - 1);
    while (n % i == 0) n /= i;
  }
  if (n > 1) r = r / n * (n - 1);
  return r;
}

long fpm(long a, long n, long mod) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

long A(long n, long mod) {
  if (n == 1) return 2 % mod;
  if (n == 2) return 4 % mod;
  if (n == 3) return 16 % mod;
  if (n == 4) return 65536 % mod;
  if (mod == 1) return 0;
  long p = phi(mod);
  return fpm(2, A(n - 1, p) + p, mod);
}

long run(int n, int mod) {
  long ret = 1 + 3 + 7 + 61;
  ret += A(7, mod) - 3;
  for (int i = 5; i <= n; ++i) {
    ret += A(1e9, mod) - 3;
  }
  return ret % mod;
}

int main() {
  std::cout << run(6, 1475789056) << std::endl;
  return 0;
}

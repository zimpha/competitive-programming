#include <bits/stdc++.h>

const int N = 100000000;

bool mark[N];
int p[N], m;

void sieve() {
  m = 0;
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mark[i * p[j]] = 0;
      if (i % p[j] == 0) break;
    }
  }
}

inline long mul_mod(long a, long b, long mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  long k = (long)((long double)a * b / mod);
  long res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

long pow_mod(long a, long n, long m) {
  long res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(long n) {
  if (n < N) return !mark[n];
  if (~n & 1) return false;
  const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
  long e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
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

//https://oeis.org/A005153
bool is_practical(long n) {
  if (n % 2) return false;
  long now = 1;
  for (long i = 2; i * i <= n; ++i) if (n % i == 0) {
    long tmp = 1, p = 1;
    while (n % i == 0) p *= i, n /= i, tmp += p;
    if (now + 1 < i) return false;
    now *= tmp;
  }
  if (n > 1 && now + 1 < n) return false;
  return true;
}

bool is_paradise(long n) {
  if (!is_prime(n - 9) || !is_prime(n - 3) || !is_prime(n + 3) || !is_prime(n + 9)) return 0;
  if (!is_practical(n - 8) || !is_practical(n + 8)) return 0;
  if (!is_practical(n - 4) || !is_practical(n + 4)) return 0;
  return is_practical(n);
}

long run(int cnt) {
  long ret = 0;
  for (long m = 840, n; ; m += 840) {
    n = m + 20;
    if ((n - 4) % 16 == 0 || (n - 4) % 11 == 0) {
      if (!is_prime(n - 1) && !is_prime(n - 7) && is_paradise(n)) {
        ret += n;
        std::cout << "get: " << n << std::endl;
        if (--cnt == 0) break;
      }
    }
    n = m + 820;
    if ((n + 4) % 16 == 0 || (n + 4) % 11 == 0) {
      if (!is_prime(n + 1) && !is_prime(n + 7) && is_paradise(n)) {
        ret += n;
        std::cout << "get: " << n << std::endl;
        if (--cnt == 0) break;
      }
    }
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(4) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

const int mod = 1000000000;
const int N = 1000000;
long t[N], d[N];
std::map<long, long> cache;

inline long mul_mod(long a, long b, long mod) {
  if (mod < int(1e9)) return a * b % mod;
  long k = (long)((long double)a * b / mod);
  long res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

long pow_mod(long a, long n, long m) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = mul_mod(r, a, m);
    a = mul_mod(a, a, m);
  }
  return r;
}

void prepare() {
  long p2 = 1, p3 = 1;
  for (int i = 1; i < N; ++i) {
    p2 = p2 * 2 % mod;
    p3 = p3 * 3 % mod;
    if (i == 1) d[i] = 1;
    else d[i] += p3 - p2;
    d[i] %= mod; d[i] += mod; d[i] %= mod;
    for (int j = i + i; j < N; j += i) d[j] -= d[i];
    t[i] = (t[i - 1] + d[i]) % mod;
  }
}

long f(long n) {
  long ret = pow_mod(3, n + 1, mod * 2) - pow_mod(2, n + 2, mod * 2) + 1;
  ret %= mod * 2; ret += mod * 2; ret %= mod * 2;
  return ret / 2;
}

// t(n) = (3^(n+1)-2^(n+2)+1)/2 - sum_{i=2}^{n} t(n/i)
long run(long n) {
  if (n < N) return t[n];
  if (cache.count(n)) return cache[n];
  long ret = f(n);
  for (long i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret -= run(n / i) * (j - i + 1) % mod;
  }
  ret %= mod; ret += mod; ret %= mod;
  return cache[n] = ret;
}

int main() {
  prepare();
  std::cout << run(10) << std::endl;
  std::cout << run(20) << std::endl;
  std::cout << run(10000000000ll) << std::endl;
  return 0;
}

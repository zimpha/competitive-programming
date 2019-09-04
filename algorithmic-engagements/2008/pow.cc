#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>

using int64 = long long;

const int mod = 999999599;
const int phi = 999999598;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// return x, where ax = 1 (mod mod)
int64 mod_inv(int64 a, int64 mod) {
  if (gcd(a, mod) != 1) return -1;
  int64 b = mod, s = 1, t = 0;
  while (b) {
    int64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

int64 crt(int n, int64 *c, int64 *m) {
  int64 M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    int64 tm = M / m[i];
    assert(tm * m[i] == M);
    int64 inv = mod_inv(tm % m[i], m[i]);
    assert(inv * tm % m[i] == 1);
    ans = (ans + tm * inv % M * c[i] % M) % M;
  }
  return (ans + M) % M;
}

const int N = 1e4;

int fac[N], inv[N];

void prepare(int n, int p) {
  fac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i < p; ++i) {
    fac[i] = i * fac[i - 1] % p;
  }
  for (int i = 2; i < p; ++i) {
    inv[i] = (p - p / i) * inv[p % i] % p;
    assert(inv[i] * i %p == 1);
  }
}

std::pair<int64, int64> factorial_p(int64 n, int p) {
  int64 a = 1, b = 0;
  for (; p <= n; n /= p) {
    b += n / p;
    a = a * fac[n % p] % p;
  }
  a = a * fac[n] % p;
  return {a, b};
}

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 calc(int n, int d, int p) {
  // n! / (d!)^(n/d) / (n/d)!
  int e = n / d;
  auto np = factorial_p(n, p);
  auto dp = factorial_p(d, p);
  auto ep = factorial_p(n / d, p);
  if (np.second - dp.second * e - ep.second > 0) return 0;
  return np.first * inv[pow_mod(dp.first, e, p)] % p * inv[ep.first] % p;
}

int64 solve(int n, int p) {
  int64 ret = 0;
  for (int d = 1; d * d <= n; ++d) if (n % d == 0) {
    ret += calc(n, d, p);
    if (d * d != n) ret += calc(n, n / d, p);
  }
  return ret % p;
}

int main() {
  int64 n, m;
  scanf("%lld%lld", &n, &m);
  int64 mods[4] = {2, 13, 5281, 7283};
  int64 res[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; ++i) {
    prepare(n, mods[i]);
    res[i] = solve(n, mods[i]);
  }
  n = crt(4, res, mods) + phi;
  int64 ret = 1;
  for (m %= mod; n; n >>= 1) {
    if (n & 1) ret = ret * m % mod;
    m = m * m % mod;
  }
  printf("%lld\n", ret);
  return 0;
}

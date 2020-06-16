#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> a(n);
  std::vector<int64> fac(n + 1, 1), ifac(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }

  auto binom = [&](int n, int m) {
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  };

  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int64 ret = 0, ways = 1;
  for (int b = 30; b >= 0; --b) {
    std::vector<int> one, zero;
    for (auto &x: a) {
      if (x >> b & 1) one.push_back(x);
      else zero.push_back(x);
    }
    if (zero.size() == 0) {
      ret += int64(k) << b;
    } else if (one.size() == 0) {
    } else if (static_cast<int>(one.size()) < k) {
      for (auto &x: one) ret += x;
      for (int i = k; i > static_cast<int>(k - one.size()); --i) {
        ways = ways * i % mod;
      }
      a = zero; k -= one.size();
    } else {
      a = one; a.push_back(zero[0]);
      for (auto &x: zero) a.back() &= x;
      ret += int64(k - 1) << b;
    }
    for (auto &x: a) if (x >> b & 1) {
      x ^= 1 << b;
    }
  }
  int64 t_ways = 0, sign = 1;
  for (int i = k; i >= 1; --i) {
    int64 w = binom(k, i) * pow_mod(i, a.size()) % mod;
    t_ways += (mod + sign) * w % mod;
    sign = -sign;
  }
  ways = t_ways % mod * ways % mod;
  printf("%lld %lld\n", ret, ways);
  return 0;
}

#include <cstdio>

using i64 = long long;

const int N = 500 + 10;
const int mod = 998244353;

i64 bernoulli[N], poly[N];
i64 fac[N], ifac[N], inv[N];
i64 coef[N][N];

i64 binom(int n, int m) {
  if (n < m) return 0;
  return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}

void prepare() {
  inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = i * fac[i - 1] % mod;
    ifac[i] = inv[i] * ifac[i - 1] % mod;
  }
  for (int i = 0; i < N; ++i) {
    bernoulli[i] = 1;
    for (int k = 0; k < i; ++k) {
      bernoulli[i] -= binom(i, k) * bernoulli[k] % mod * inv[i - k + 1] % mod;
    }
    bernoulli[i] %= mod;
    bernoulli[i] = (bernoulli[i] + mod) % mod;
  }
  for (int p = 0; p < N - 1; ++p) {
    for (int j = 0; j <= p; ++j) {
      coef[p][p + 1 - j] = binom(p + 1, j) * bernoulli[j] % mod;
      coef[p][p + 1 - j] *= inv[p + 1];
      coef[p][p + 1 - j] %= mod;
    }
  }
}

i64 pow_sum(i64 n, int p) {
  i64 ret = 0, w = 1;
  n %= mod;
  for (int i = 0; i <= p + 1; ++i) {
    ret += coef[p][i] * w % mod;
    w = w * n % mod;
  }
  return ret % mod;
}

int main() {
  prepare();
  i64 n;
  int m;
  scanf("%lld%d", &n, &m);
  i64 ret = (n % m == 0);
  if (m % 2 == 0) ret = mod - ret; 
  i64 n_mod = n % mod;
  for (int k = 1; k < m; ++k) {
    poly[0] = 1;
    for (int i = 1; i <= m - k - 1; ++i) {
      poly[i] = 0;
      // poly * (n - kx - i)
      // poly * (n - i) - k * x * poly
      for (int j = i; j >= 1; --j) {
        poly[j] = poly[j] * (n_mod - i) % mod - k * poly[j - 1];
        poly[j] %= mod;
        poly[j] = (poly[j] + mod) % mod;
      }
      poly[0] = poly[0] * (n_mod - i + mod) % mod;
    }
    i64 now = 0;
    for (int i = 0; i <= m - k - 1; ++i) {
      now += pow_sum((n - m + k) / k, i) * poly[i] % mod;
    }
    now %= mod;
    now = now * ifac[m - k - 1] % mod;
    now = now * binom(m, k) % mod;
    if (k & 1) ret += now;
    else ret -= now;
  }
  ret %= mod;
  ret = (ret + mod) % mod;
  printf("%lld\n", ret);
  return 0;
}

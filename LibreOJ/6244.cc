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
  int n, k, x;
  scanf("%d%d%d", &n, &k, &x);
  std::vector<int> fact(n + 1, 1), ifact(n + 1, 1);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fact[i] = 1ll * i * fact[i - 1] % mod;
    ifact[i] = pow_mod(fact[i], mod - 2);
  }
  auto binom = [&](int n, int m) {
    return 1ll * fact[n] * ifact[m] % mod * ifact[n - m] % mod;
  };
  int ret = 0;
  for (int i = 0; i <= k - x; ++i) {
    int64 now = binom(k - x, i) * binom(n - x - i, k - x - i) % mod * fact[k - x - i] % mod;
    if (i & 1) ret += mod - now;
    else ret += now;
    ret %= mod;
  }
  ret = ret * binom(k, x) % mod;
  printf("%d\n", ret);
  return 0;
}

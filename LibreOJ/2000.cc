#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 1000000 + 10, mod = 1e9 + 7;

int fib[N], ifib[N], g[N], ig[N], mu[N];

int inv(int x) {
  return x == 1 ? 1 : int64(mod - mod / x) * inv(mod % x) % mod;
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  fib[0] = 0;
  for (int i = 1; i < N; ++i) {
    fib[i] = i < 2 ? i : (fib[i - 1] + fib[i - 2]) % mod;
    ifib[i] = inv(fib[i]);
    mu[i] += i == 1;
    g[i] = 1;
    for (int j = i + i; j < N; j += i) mu[j] -= mu[i];
  }
  for (int i = 1; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      g[j] = (int64)g[j] * (mu[j / i] == 0 ? 1 : (mu[j / i] == 1 ? fib[i] : ifib[i])) % mod;
    }
  }
  ig[0] = g[0] = 1;
  for (int i = 1; i < N; ++i) {
    ig[i] = (int64)ig[i - 1] * inv(g[i]) % mod;
    g[i] = (int64)g[i] * g[i - 1] % mod;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    int64 ret = 1;
    for (int i = 1, j; i <= n && i <= m; i = j + 1) {
      j = std::min(n / (n / i), m / (m / i));
      ret = ret * pow_mod((int64)g[j] * ig[i - 1] % mod, int64(n / j) * (m / j)) % mod;
    }
    printf("%lld\n", ret);
  }
  return 0;
}

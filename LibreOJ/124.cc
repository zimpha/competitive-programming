#include <cstdio>

using int64 = long long;

const int N = 10000000 + 10;
const int mod = 1e9 + 7;

int p[N / 10], pw[N / 10], e[N], f[N], g[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, k, m = 0;
  scanf("%d%d", &n, &k);
  for (int i = 2; i <= n; ++i) {
    if (!f[i]) {
      pw[m] = pow_mod(i, k);
      e[i] = f[i] = 1 + pw[m];
      g[i] = 1;
      p[m++] = i;
    }
    for (int j = 0, u = n / i, v; j < m && p[j] <= u; ++j) {
      f[v = i * p[j]] = 1;
      if (i % p[j] == 0) {
        g[v] = g[i];
        e[v] = ((int64)e[i] * pw[j] + 1) % mod;
        f[v] = (int64)g[v] * e[v] % mod;
        break;
      } else {
        f[v] = (int64)f[i] * (1 + pw[j]) % mod;
        g[v] = f[i];
        e[v] = 1 + pw[j];
      }
    }
  }
  int64 ret = 1;
  for (int i = 2; i <= n; ++i) {
    ret += f[i];
  }
  printf("%lld\n", ret % mod);
  return 0;
}

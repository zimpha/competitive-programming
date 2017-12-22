#include <cstdio>

using int64 = long long;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 f[N], phi[N], g[N], e[N];
int64 p[N], pk[N];

int64 gcd(int64 a, int64 b) {
  return b ? gcd(b, a % b) : a;
}

int64 brute(int l, int r, int k) {
  int64 ret = 0;
  for (int j = l; j <= r; ++j) {
    for (int i = 1; i <= j; ++i) {
      ret += pow_mod(gcd(i, j), k);
    }
    ret %= mod;
  }
  return ret;
}

int main() {
  int k, m = 0;
  scanf("%d", &k);
  f[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!f[i]) {
      pk[m] = pow_mod(i, k);
      e[i] = f[i] = (i - 1 + pk[m]) % mod;
      g[i] = 1;
      phi[i] = i - 1;
      p[m++] = i;
    }
    for (int j = 0, u = (N - 1) / i, v; j < m && p[j] <= u; ++j) {
      f[v = i * p[j]] = 1;
      if (i % p[j] == 0) {
        g[v] = g[i];
        phi[v] = phi[i] * p[j];
        e[v] = (e[i] * pk[j] + phi[v]) % mod;
        f[v] = g[v] * e[v] % mod;
        break;
      } else {
        f[v] = f[i] * f[p[j]] % mod;
        phi[v] = p[j] - 1;
        g[v] = f[i];
        e[v] = f[p[j]];
      }
    }
  }
  for (int i = 1; i < N; ++i) {
    f[i] = (f[i - 1] + f[i]) % mod;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", (f[r] - f[l - 1] + mod) % mod);
  }
  return 0;
}

// https://arxiv.org/ftp/arxiv/papers/1501/1501.04750.pdf
#include <cstdio>
#include <cstring>

using int64 = long long;

const int N = 1e5 + 10, mod = 1e9 + 7;

int fac[N], ifac[N], inv[N];

int calc(int n, int m) {
  int ret = 0;
  for (int64 j = -m; j <= m; ++j) {
    if (m + j * (n + 2) < 0) continue;
    int64 s = (m + (n + 2) * j) / 2;
    if (s < 0 || s > m) continue;
    int binom = (int64)fac[m] * ifac[s] % mod * ifac[m - s] % mod;
    if (j % 2 == 0) ret += binom;
    else ret += mod - binom;
    ret %= mod;
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  inv[1] = 1;
  for (int i = 2; i <= m; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
  }
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= m; ++i) {
    fac[i] = (int64)i * fac[i - 1] % mod;
    ifac[i] = (int64)inv[i] * ifac[i - 1] % mod;
  }
  int ret = calc(n - 1, m) - calc(n - 2, m);
  printf("%d\n", (ret % mod + mod) % mod);
  return 0;
}

#include <cstdio>

using int64 = long long;

const int N = 1e5 + 10, K = 30, mod = 1e9 + 9;

int64 binom[K][K];
int64 f[N][K], g[N][K];

int main() {
  for (int i = 0; i < K; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  for (int i = 0; i <= 26; ++i) f[1][i] = i;
  for (int j = 1; j <= 26; ++j) {
    int64 p = j;
    for (int i = 2; i < N; ++i) {
      p = p * j % mod;
      f[i][j] = (i % 2 ? f[i - 1][j] * j : f[i - 1][j] * j - f[i / 2][j]) % mod;
      if (f[i][j] < 0) f[i][j] += mod;
      g[i][j] = p - f[i][j];
      for (int k = 1; k < j; ++k) {
        g[i][j] = (g[i][j] - g[i][k] * binom[j][k]) % mod;
      }
      if (g[i][j] < 0) g[i][j] += mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%lld\n", g[n][k] * binom[26][k] % mod);
  }
  return 0;
}

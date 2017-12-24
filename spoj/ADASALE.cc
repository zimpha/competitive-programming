#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 3000 + 10;
const int64 inf = 1ll << 60;

int64 f[2][N], g[2][N], L[N], P[N];
int n, k, mod;

int main() {
  scanf("%d%d%d", &n, &k, &mod);
  for (int i = 0; i < n; ++i) scanf("%lld", &L[i]);
  for (int i = 0; i < n; ++i) scanf("%lld", &P[i]);
  for (int i = 0; i <= k; ++i) {
    f[0][i] = f[1][i] = -inf;
  }
  f[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k; ++j) {
      g[0][j] = std::max(f[0][j], f[1][j]);
      g[1][j] = std::max(f[0][j], f[1][j]) - L[i];
    }
    int64 mx = g[1][0], sum = 0;
    for (int j = 1; j <= k; ++j) {
      sum += P[i] * (i + 1) * j % mod;
      if (g[1][j] != -inf) {
        mx = std::max(mx, g[1][j] + sum);
      }
    }
    for (int j = 0; j <= k; ++j) {
      mx -= P[i] * (i + 1) * j % mod;
      g[1][j] = std::max(mx, -inf);
    }
    for (int j = 0; j <= k; ++j) {
      f[0][j] = g[0][j];
      f[1][j] = g[1][j];
    }
  }
  int64 ret = 0;
  for (int i = 0; i <= k; ++i) {
    ret = std::max(ret, std::max(f[0][i], f[1][i]));
  }
  printf("%lld\n", ret);
  return 0;
}

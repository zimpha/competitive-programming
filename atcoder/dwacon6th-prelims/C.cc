#include <cstdio>
#include <vector>

const int N = 1000 + 10, M = 20 + 10;
const int mod = 1e9 + 7;

int binom[N][N], dp[M][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(m);
  for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
  for (int i = 0; i <= n; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  dp[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= n; ++j) {
      for (int k = 0; j + k <= n && k <= a[i]; ++k) {
        dp[i + 1][j + k] += 1ll * dp[i][j] * binom[n - j][k] % mod * binom[n - k][a[i] - k] % mod;
        if (dp[i + 1][j + k] >= mod) dp[i + 1][j + k] -= mod;
      }
    }
  }
  printf("%d\n", dp[m][n]);
  return 0;
}

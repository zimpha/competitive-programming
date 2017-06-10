#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100 + 10, mod = 1e9 + 7;

int dp[N][N][N];
int nx[N], pv[N];
int a[N], n;

int solve(int i, int j, int l) {
  if (dp[i][j][l] != -1) return dp[i][j][l];
  int mx = std::max(a[i], a[j]);
  int ret = 0;
  for (int k = i + 1; k < j; ++k) if (a[k] >= mx) {
    if (pv[k] <= i && a[k] != a[j]) {
      int c = std::max(0, a[k] - l);
      if (c) ret += 1ll * c * solve(k, j, l + 1) % mod;
    }
    ret %= mod;
    if (nx[k] >= j) {
      int c = std::max(0, a[k] - l);
      if (c) ret += 1ll * c * solve(i, k, l + 1) % mod;
    }
    ret %= mod;
  }
  if (a[i] > a[j]) ret = (ret + 1) % mod;
  return dp[i][j][l] = ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
    }
    a[0] = 0;
    a[n + 1] = -1;
    for (int i = 1; i <= n; ++i) {
      pv[i] = -1;
      for (int j = i - 1; j >= 1; --j) {
        if (a[i] != a[j]) continue;
        pv[i] = j;
        break;
      }
      nx[i] = n + 1;
      for (int j = i + 1; j <= n; ++j) {
        if (a[i] != a[j]) continue;
        nx[i] = j;
        break;
      }
    }
    memset(dp, -1, sizeof(dp));
    printf("Case #%d: %d\n", cas, solve(0, n + 1, 0));
  }
  return 0;
}

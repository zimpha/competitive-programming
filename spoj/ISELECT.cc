#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 10000 + 10;
const int64 inf = 1ll << 60;

int64 a[N][2], dp[N][2];
int n;

int64 solve(int o) {
  dp[0][o] = a[0][o];
  dp[0][!o] = -inf;
  for (int i = 1; i < n; ++i) {
    dp[i][0] = dp[i][1] = -inf;
    dp[i][0] = dp[i - 1][1] + a[i][0];
    dp[i][1] = std::max(dp[i - 1][0], dp[i - 1][1]) + a[i][1];
  }
  if (!o) return dp[n - 1][1];
  else return std::max(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i][0]);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i][1]);
    for (int i = 0; i < n; ++i) a[i][1] = -a[i][1];
    printf("%lld\n", std::max(solve(0), solve(1)));
  }
  return 0;
}

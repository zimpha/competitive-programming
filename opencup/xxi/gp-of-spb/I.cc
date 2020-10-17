#include <cstdio>

const int N = 500 + 10;

int dp[N * N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= m; ++i) dp[i] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = m; j >= i; --j) {
      dp[j] ^= dp[j - i];
    }
    for (int j = 1; j <= m; ++j) dp[j] ^= dp[j - 1];
  }
  printf("%d\n", dp[m] ^ (m == 0 ? 0 : dp[m - 1]));
  return 0;
}

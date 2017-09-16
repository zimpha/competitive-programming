#include <cstdio>
#include <cstring>

const int N = 3e5 + 10, M = 40;

int dp[2][M];

int main() {
  int n;
  scanf("%d", &n);
  memset(dp, -1, sizeof(dp));
  auto update = [] (int &x, int y) {
    if (x == -1 || x > y) x = y;
  };
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    int t = i & 1, x;
    memset(dp[t ^ 1], -1, sizeof(dp[t ^ 1]));
    scanf("%d", &x); x /= 100;
    for (int j = 0; j < M; ++j) {
      if (dp[t][j] == -1) continue;
      update(dp[t ^ 1][j + x / 10], dp[t][j] + x);
      for (int k = 1; k <= x && k <= j; ++k) {
        update(dp[t ^ 1][j - k], dp[t][j] + x - k);
      }
    }
  }
  int ret = -1;
  for (int i = 0; i < M; ++i) {
    if (dp[n & 1][i] == -1) continue;
    if (ret == -1 || dp[n & 1][i] < ret) {
      ret = dp[n & 1][i];
    }
  }
  printf("%d\n", ret * 100);
  return 0;
}
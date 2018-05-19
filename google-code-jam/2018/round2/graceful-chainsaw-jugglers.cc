#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 500 + 10;

int dp[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int R, B;
    scanf("%d%d", &R, &B);
    memset(dp, 0, sizeof(dp));
    for (int r = 0; r * r <= R * 2 && r <= R; ++r) {
      for (int b = 0; b * b <= B * 2 && b <= B; ++b) {
        if (!r && !b) continue;
        for (int i = R; i >= r; --i) {
          for (int j = B; j >= b; --j) {
            dp[i][j] = std::max(dp[i][j], dp[i - r][j - b] + 1);
          }
        }
      }
    }
    int ret = 0;
    for (int i = 0; i <= R; ++i) {
      for (int j = 0; j <= B; ++j) {
        ret = std::max(ret, dp[i][j]);
      }
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

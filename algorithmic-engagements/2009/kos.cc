#include <cstdio>
#include <cstring>

const int N = 550 + 10;

double dp[N * 6];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n > 550 || k > n * 6 || k < n) puts("0");
    else {
      memset(dp, 0, sizeof(dp));
      dp[0] = 1;
      for (int i = 1; i <= n; ++i) {
        for (int j = i * 6; j >= 0; --j) {
          dp[j] = 0;
          for (int k = 1; k <= 6 && k <= j; ++k) {
            dp[j] += dp[j - k];
          }
          dp[j] /= 6;
        }
      }
      printf("%d\n", int(dp[k] * 100 + 1e-6));
    }
  }
  return 0;
}

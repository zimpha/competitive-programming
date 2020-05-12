#include <cstdio>

using int64 = long long;

const int N = 1e5 + 10;

int a[N];
int64 dp[N][3], ret[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  dp[0][0] = 0;
  dp[0][1] = a[0];
  dp[0][2] = a[0] * 2;
  for (int i = 0; i < n; ++i) ret[i] = -1;
  for (int e = 0; e < 3; ++e) {
    dp[0][0] = dp[0][1] = dp[0][2] = -1;
    dp[0][e] = a[0] * e;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < 3; ++j) {
        dp[i][j] = -1;
        for (int k = 0; k < 3; ++k) if (j + k >= 2 && dp[i - 1][k] != -1) {
          int64 w = dp[i - 1][k] + a[i] * j;
          if (dp[i][j] == -1 || w < dp[i][j]) dp[i][j] = w;
        }
        if (j + e >= 2 && (ret[i] == -1 || ret[i] > dp[i][j])) {
          ret[i] = dp[i][j];
        }
      }
    }
  }
  for (int i = 2; i < n; ++i) printf("%.1f ", ret[i] * 0.5);
  puts("");
  return 0;
}

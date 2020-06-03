#include <cstdio>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  int dp[3];
  for (int i = 0; i < 3; ++i) scanf("%d", &dp[i]);
  for (int i = 1; i < n; ++i) {
    int t[3];
    for (int j = 0; j < 3; ++j) {
      scanf("%d", &t[j]);
      int mx = 0;
      for (int k = 0; k < 3; ++k) {
        if (k != j) mx = std::max(mx, dp[k]);
      }
      t[j] += mx;
    }
    for (int j = 0; j < 3; ++j) dp[j] = t[j];
  }
  printf("%d\n", std::max(dp[0], std::max(dp[1], dp[2])));
  return 0;
}

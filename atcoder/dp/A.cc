#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> h(n), dp(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    if (!i) dp[i] = 0;
    else dp[i] = 2e9;
    if (i >= 1) {
      dp[i] = std::min(dp[i], dp[i - 1] + std::abs(h[i] - h[i - 1]));
    }
    if (i >= 2) {
      dp[i] = std::min(dp[i], dp[i - 2] + std::abs(h[i] - h[i - 2]));
    }
  }
  printf("%d\n", dp.back());
  return 0;
}

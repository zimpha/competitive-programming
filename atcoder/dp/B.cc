#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> h(n), dp(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    if (!i) dp[i] = 0;
    else dp[i] = 2e9;
    for (int j = i - 1; j >= i - k && j >= 0; --j) {
      dp[i] = std::min(dp[i], dp[j] + std::abs(h[i] - h[j]));
    }
  }
  printf("%d\n", dp.back());
  return 0;
}

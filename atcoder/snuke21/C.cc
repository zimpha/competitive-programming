#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> states(n);
  for (int i = 0; i < n; ++i) {
    char s[20];
    scanf("%s", s);
    for (int j = 0; j < 12; ++j) {
      states[i] |= (s[j] == 'o') << j;
    }
  }
  std::vector<int> dp(1 << 12, -1);
  dp[0] = 0;
  int ret = 0;
  for (int mask = 0; mask < (1 << 12); ++mask) if (dp[mask] != -1) {
    ret = std::max(ret, dp[mask]);
    for (int i = 0; i < n; ++i) if ((mask | states[i]) != mask) {
      dp[mask | states[i]] = std::max(dp[mask | states[i]], dp[mask] + 1);
    }
  }
  printf("%d\n", ret);
  return 0;
}

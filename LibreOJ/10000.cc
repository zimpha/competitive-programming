#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> s(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &s[i].first, &s[i].second);
  }
  std::sort(s.begin(), s.end());
  std::vector<int> dp(n, 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (s[j].second <= s[i].first) {
        dp[i] = std::max(dp[i], dp[j] + 1);
      }
    }
  }
  printf("%d\n", *max_element(dp.begin(), dp.end()));
  return 0;
}

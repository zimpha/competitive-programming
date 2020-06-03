#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> dp(m + 1);
  for (int i = 0; i < n; ++i) {
    int w, v;
    scanf("%d%d", &w, &v);
    for (int j = m; j >= w; --j) {
      dp[j] = std::max(dp[j], dp[j - w] + v);
    }
  }
  printf("%lld\n", *std::max_element(dp.begin(), dp.end()));
  return 0;
}

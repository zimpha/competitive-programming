#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> dp(100 * 1000 + 1, -1);
  dp[0] = 0;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int w, v;
    scanf("%d%d", &w, &v);
    s += v;
    for (int j = s; j >= v; --j) if (dp[j - v] != -1) {
      if (dp[j] == -1 || dp[j] > dp[j - v] + w) {
        dp[j] = dp[j - v] + w;
      }
    }
  }
  for (int i = 100 * 1000; i >= 0; --i) {
    if (dp[i] <= m && dp[i] != -1) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}

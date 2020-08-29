#include <cstdio>
#include <vector>

class Solution {
 public:
  /**
   * @param heights: the heights of buildings.
   * @param k: the vision.
   * @param x: the energy to spend of the first action.
   * @param y: the energy to spend of the second action.
   * @return: the minimal energy to spend.
   */
  long long shuttleInBuildings(std::vector<int> &heights, int k, int x, int y) {
    int n = heights.size();
    std::vector<long long> dp(n, 1ll << 60);
    std::vector<int> next(n);
    for (int i = n - 1; i >= 0; --i) {
      int j = i + 1;
      while (j < n && heights[j] <= heights[i]) j = next[j];
      next[i] = j;
    }
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
      if (next[i] != n && next[i] - i <= k) {
        dp[next[i]] = std::min(dp[next[i]], dp[i] + x);
      }
      for (int d = 1; d <= 2; ++d) if (i + d < n) {
        dp[i + d] = std::min(dp[i + d], dp[i] + y);
      }
    }
    return dp.back();
  }
};

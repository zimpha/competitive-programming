#include <vector>
#include <algorithm>

class Solution {
 public:
  /**
   * @param trees: the positions of trees.
   * @param d: the minimum beautiful interval.
   * @return: the minimum number of trees to remove to make trees beautiful.
   */
  int treePlanning(std::vector<int> &trees, int d) {
    // write your code here.
    int n = trees.size();
    std::vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
      int w = trees[i] - d;
      int x = std::upper_bound(trees.begin(), trees.end(), w) - trees.begin() - 1;
      if (x < 0) dp[i] = 1;
      else dp[i] = dp[x] + 1;
      if (i) dp[i] = std::max(dp[i], dp[i - 1]);
    }
    return n - dp.back();
  }
};

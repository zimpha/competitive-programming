#include <vector>
#include <map>
#include <algorithm>

class Solution {
 public:
  /**
   * @param lengths: the lengths of sticks at the beginning.
   * @return: return the minimum number of cuts.
   */
  int makeEquilateralTriangle(std::vector<int> &lengths) {
    // write your code here.
    int ret = 2;
    std::map<int, int> mp;
    for (auto &x: lengths) mp[x]++;
    for (auto &e: mp) {
      if (e.second >= 3) return 0;
    }
    for (auto &e: mp) if (e.second == 2) {
      for (auto &x: lengths) if (x > e.first) return 1;
    }
    for (auto &e: mp) {
      for (auto &x: lengths) {
        if (x == e.first * 2) return 1;
      }
    }
    return ret;
  }
};

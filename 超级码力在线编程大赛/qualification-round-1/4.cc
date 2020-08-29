#include <string>

int dp[3000][3000];

class Solution {
 public:
  /**
   * @param s: a string.
   * @return: return the values of all the intervals.
   */
  long long suffixQuery(std::string &s) {
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      for (int j = n - 1; j >= 0; --j) {
        if (s[i] == s[j]) {
          dp[i][j] = (i > 0 && j + 1 < n) ? dp[i - 1][j + 1] + 1 : 1;
        } else {
          dp[i][j] = 0;
        }
      }
    }
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        int l = dp[j][i];
        if (l > j - i + 1) l = j - i + 1;
        ret += l;
      }
    }
    return ret;
  }
};

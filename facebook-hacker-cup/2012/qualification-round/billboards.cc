#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int w, h;
    std::cin >> w >> h;
    std::string line;
    std::getline(std::cin, line);
    std::stringstream sin(line);
    std::vector<std::string> words;
    while (sin >> line) {
      words.emplace_back(line);
    }
    auto check = [&](int s) {
      int n = h / s, m = w / s;
      if (n <= 0 || m <= 0) return false;
      std::vector<int> dp(words.size() + 1, 1e9);
      dp[0] = 0;
      for (size_t i = 0; i < words.size(); ++i) {
        if (dp[i] == 1e9) continue;
        int len = 0;
        for (int j = i; j < words.size(); ++j) {
          len += words[j].size();
          if (len + j - i > m) break;
          dp[j + 1] = std::min(dp[j + 1], dp[i] + 1);
        }
      }
      return dp.back() <= n;
    };
    int l = 1, r = h;
    while (l < r) {
      int m = (l + r + 1) >> 1;
      if (check(m)) l = m;
      else r = m - 1;
    }
    printf("Case #%d: %d\n", cas, l);
  }
  return 0;
}

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::string line;
    if (cas == 1) std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::vector<int> cnt(26), base(26);
    for (auto &&c: std::string("HACKERCUP")) {
      base[c - 'A']++;
    }
    for (auto &&c: line) {
      if (c >= 'A' && c <= 'Z') cnt[c - 'A']++;
    }
    int ret = 0;
    while (true) {
      for (int i = 0; i < 26; ++i) cnt[i] -= base[i];
      if (*std::min_element(cnt.begin(), cnt.end()) < 0) break;
      ++ret;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
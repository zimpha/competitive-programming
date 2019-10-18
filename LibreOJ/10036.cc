#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  for (std::string s; std::cin >> s; ) {
    std::vector<int> fail(s.size(), -1);
    for (size_t i = 1; i < s.size(); ++i) {
      int &j = fail[i];
      for (j = fail[i - 1]; j >= 0 && s[j + 1] != s[i]; j = fail[j]);
      if (s[j + 1] == s[i]) ++j;
    }
    std::vector<int> ret;
    for (int i = s.size() - 1; i != -1; i = fail[i]) {
      ret.push_back(i + 1);
    }
    std::reverse(ret.begin(), ret.end());
    for (auto &x: ret) printf("%d ", x);
    puts("");
  }
  return 0;
}

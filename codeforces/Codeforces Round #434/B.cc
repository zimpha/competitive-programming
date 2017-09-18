#include <cstdio>
#include <set>
#include <vector>
#include <string>
#include <iostream>

const int S = 100000000;

char cnt[S];

int main() {
  int n;
  std::cin >> n;
  std::vector<std::string> ret(n);
  std::vector<std::string> s(n);
  std::vector<std::set<int>> all(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    ret[i] = s[i];
  }
  int pw = 100000000;
  for (int len = 8; len >= 1; --len) {
    for (int i = 0; i < pw; ++i) cnt[i] = 0;
    pw /= 10;
    for (int i = 0; i < n; ++i) {
      int now = 0;
      all[i].clear();
      for (int j = 0; j < len; ++j) now = now * 10 + s[i][j] - '0';
      all[i].insert(now);
      for (int j = len; j < 9; ++j) {
        now -= (s[i][j - len] - '0') * pw;
        now = now * 10 + s[i][j] - '0';
        all[i].insert(now);
      }
      for (auto &&s: all[i]) {
        cnt[s]++;
        if (cnt[s] > 2) cnt[s] = 2;
      }
    }
    for (int i = 0; i < n; ++i) {
      for (auto &&s: all[i]) if (cnt[s] == 1) {
        ret[i] = std::to_string(s);
        while (ret[i].size() < len) ret[i] = '0' + ret[i];
        break;
      }
    }
  }
  for (int i = 0; i < n; ++i) printf("%s\n", ret[i].c_str());
  return 0;
}

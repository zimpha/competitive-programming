#include <cstdio>
#include <cassert>
#include <string>
#include <iostream>
#include <map>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::map<std::pair<int, int>, std::pair<int, int>> mp;
    int n, b, f;
    std::cin >> n >> b >> f;
    std::string s(n, ' ');
    for (int i = 0; i < n; ++i) {
      int t = i / 16;
      s[i] = '0' + (t & 1);
    }
    std::cout << s << std::endl;
    std::cin >> s;
    for (size_t i = 0, j, k = 0; i < s.size(); i = j, ++k) {
      for (j = i; j < s.size() && s[i] == s[j]; ++j);
      int l = k * 16, r = std::min<int>(k * 16 + 16, n);
      mp[{l, r}] = {i, j};
    }
    for (int it = 1; it < f; ++it) {
      std::string s;
      for (auto &&e: mp) {
        int len = e.first.second - e.first.first;
        for (int i = 0; i < len / 2; ++i) s.push_back('0');
        for (int i = 0; i < len - len / 2; ++i) s.push_back('1');
      }
      std::cout << s << std::endl;
      std::cin >> s;
      std::map<std::pair<int, int>, std::pair<int, int>> new_mp;
      for (auto &&e: mp) {
        auto dst = e.second;
        int zero = 0, one = 0;
        for (int i = dst.first; i < dst.second; ++i) {
          if (s[i] == '0') ++zero;
          else ++one;
        }
        int len = e.first.second - e.first.first;
        int l = e.first.first, m = l + len / 2, r = e.first.second;
        if (l < m) new_mp[{l, m}] = {dst.first, dst.first + zero};
        if (m < r) new_mp[{m, r}] = {dst.first + zero, dst.second};
      }
      mp.swap(new_mp);
    }
    for (auto &&e: mp) {
      if (e.second.first == e.second.second) std::cout << e.first.first << " ";
    }
    std::cout << std::endl;
    std::cin >> s;
  }
  return 0;
}

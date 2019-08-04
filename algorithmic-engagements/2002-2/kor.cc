#include <set>
#include <unordered_set>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using uint64 = unsigned long long;

const uint64 seed = 1e9 + 7;

uint64 hash(const std::string &s) {
  uint64 r = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    r = r * seed + s[i];
  }
  return r;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  std::vector<std::pair<char, int>> letters(n);
  std::vector<std::pair<uint64, std::unordered_set<uint64>>> hashes(n);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> letters[i].first >> s;
    letters[i].second = s.size();
    hashes[i].first = hash(s);
    for (size_t j = 0; j < s.size(); ++j) {
      s[j] = '0' + '1' - s[j];
      hashes[i].second.emplace(hash(s));
      s[j] = '0' + '1' - s[j];
    }
  }
  int m;
  std::cin >> m;
  for (int cas = 1; cas <= m; ++cas) {
    std::string s;
    std::cin >> s;
    std::vector<std::vector<int>> ways(s.size() + 1, std::vector<int>(2));
    std::vector<std::vector<int>> from(s.size() + 1, std::vector<int>(2));
    std::vector<uint64> h(s.size() + 1), pw(s.size() + 1, 1);
    for (int i = 1; i <= (int)s.size(); ++i) {
      pw[i] = pw[i - 1] * seed;
    }
    for (int i = s.size() - 1; i >= 0; --i) {
      h[i] = h[i + 1] * seed + s[i];
    }
    ways[0][0] = 1;
    for (int i = 1; i <= (int)s.size(); ++i) {
      for (int j = 0; j < n; ++j) if (i >= letters[j].second) {
        uint64 hash = h[i - letters[j].second] - h[i] * pw[letters[j].second];
        int e = 0;
        if (hash == hashes[j].first) e = 0;
        else if (hashes[j].second.count(hash)) e = 1;
        else continue;
        for (int o = e; o < 2; ++o) {
          ways[i][o] += ways[i - letters[j].second][o - e];
          if (ways[i][o] > 2) ways[i][o] = 2;
          if (ways[i - letters[j].second][o - e]) from[i][o] = (j << 1) | e;
        }
      }
    }
    if (ways[s.size()][0] + ways[s.size()][1] == 0) puts("BLAD");
    else if (ways[s.size()][0] + ways[s.size()][1] > 1) puts("ZBYT WIELE");
    else {
      int i = s.size(), j = ways[i][0] ? 0 : 1;
      std::vector<char> ret;
      for (; i > 0; ) {
        int p = from[i][j] >> 1;
        int e = from[i][j] & 1;
        ret.push_back(letters[p].first);
        i -= letters[p].second;
        j -= e;
      }
      std::reverse(ret.begin(), ret.end());
      puts("OK");
      for (auto &c: ret) putchar(c);
      puts("");
    }
  }
  return 0;
}

#include <cstdio>
#include <string>
#include <set>
#include <iostream>

using uint64 = unsigned long long;

const int seed = 1e9 + 7;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  std::set<uint64> s;
  for (int i = 0; i < n; ++i) {
    std::string line;
    if (!i) std::getline(std::cin, line);
    std::getline(std::cin, line);
    if (line[0] == 'a') {
      line = line.substr(4);
      uint64 h = 0;
      for (auto &c: line) h = h * seed + c;
      s.insert(h);
    } else {
      line = line.substr(5);
      uint64 h = 0;
      for (auto &c: line) h = h * seed + c;
      puts(s.count(h) ? "yes" : "no");
    }
  }
  return 0;
}

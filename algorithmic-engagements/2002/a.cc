#include <cstdio>
#include <string>
#include <set>
#include <iostream>

int main() {
  int n;
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> n;
  std::set<std::string> s;
  for (int i = 0; i < n; ++i) {
    std::string l;
    std::cin >> l;
    std::string t;
    for (auto &&c: l) {
      if ('A' <= c && c <= 'Z') c = c - 'A' + 'a';
      if (c != '-') t.push_back(c);
    }
    s.insert(t);
  }
  std::cout << s.size() << std::endl;
  return 0;
}

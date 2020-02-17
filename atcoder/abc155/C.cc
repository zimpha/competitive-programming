#include <iostream>
#include <string>
#include <map>

int main() {
  int n;
  std::cin >> n;
  std::map<std::string, int> mp;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    mp[s]++;
  }
  int mx = 0;
  for (auto &e: mp) {
    if (e.second > mx) mx = e.second;
  }
  for (auto &e: mp) {
    if (e.second == mx) std::cout << e.first << std::endl;
  }
  return 0;
}

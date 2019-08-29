#include <cstdio>
#include <string>
#include <iostream>

bool valid(const std::string& s) {
  for (size_t i = 0; i < s.size(); ++i) {
    if (i >= 1 && s[i] == s[i - 1]) return true;
    if (i >= 2 && s[i] == s[i - 2]) return true;
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  int a = 0, b = 0;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    a += valid(s);
    for (auto &c: s) {
      if (c == 'j') c = 'i';
      if (c == 'b') c = 'p';
      if (c == 'd') c = 'p';
    }
    b += valid(s);
  }
  printf("%d\n%d\n", a, b);
  return 0;
}

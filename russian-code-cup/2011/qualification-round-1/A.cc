#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

int main() {
  std::string s;
  std::cin >> s;
  std::string ret;
  for (size_t i = 0, j; i < s.size(); ++i) {
    if (s[i] == '(') {
      for (j = i; s[j] != ')'; ++j);
      std::string t = s.substr(i + 1, j - i - 1);
      i = j;
      std::reverse(t.begin(), t.end());
      ret += t;
    } else {
      ret += s[i];
    }
  }
  std::cout << ret << std::endl;
  return 0;
}

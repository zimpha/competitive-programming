#include <cstdio>
#include <string>
#include <iostream>

bool is_pal(std::string& s) {
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] != s[s.size() - 1 - i]) return false;
  }
  return true;
}

int main() {
  std::string s;
  std::cin >> s;
  int cnt = 0;
  for (int i = 0; i < s.size(); ++i) {
    cnt += s[i] != s[0];
  }
  if (cnt > 1) {
    for (int i = 0; i < s.size(); ++i) {
      std::string t = s.substr(i + 1) + s.substr(0, i + 1);
      if (is_pal(t) && t != s) {
        puts("1");
        return 0;
      }
    }
    puts("2");
  } else {
    puts("Impossible");
  }
  return 0;
}

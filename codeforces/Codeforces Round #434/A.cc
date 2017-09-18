#include <cstdio>
#include <iostream>

bool valid(char c) {
  return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u';
}

int main() {
  std::string s;
  std::cin >> s;
  int cnt = 0, all_same = true;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (valid(s[i])) {
      all_same &= (cnt == 0 || s[i] == s[i - 1]);
      ++cnt;
    } else {
      cnt = 0;
      all_same = true;
    }
    if (cnt >= 3 && !all_same) {
      putchar(' ');
      cnt = valid(s[i]);
      all_same = true;
      cnt = 1;
    }
    putchar(s[i]);
  }
  puts("");
  return 0;
}

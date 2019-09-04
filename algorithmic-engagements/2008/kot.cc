#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> s = {
  "`1234567890-=",
  "QWERTYUIOP[]\\",
  "ASDFGHJKL;'",
  "ZXCVBNM,./",
  " "
};

int main() {
  int map[256];
  for (int i = 0; i < 5; ++i) {
    for (auto &c: s[i]) map[(int)c] = i + 1;
  }
  std::string line;
  std::getline(std::cin, line);
  for (auto &c: line) putchar('0' + map[(int)c]);
  puts("");
  return 0;
}

#include <bits/stdc++.h>

void run() {
  std::string s;
  std::cin >> s;
  bool flag = false;
  for (auto &&c: s) {
    flag |= c != 'a';
  }
  if (!flag) {
    s.back() = 'z';
    std::cout << s << std::endl;
  } else {
    int i, j;
    for (i = 0; s[i] == 'a'; ++i);
    for (j = i; j < s.size() && s[j] != 'a'; ++j);
    for (; i < j; ++i) s[i]--;
    std::cout << s << std::endl;
  }
}

int main() {
  run();
  return 0;
}

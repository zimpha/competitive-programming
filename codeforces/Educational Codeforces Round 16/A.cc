#include <bits/stdc++.h>

void run() {
  std::string s;
  std::cin >> s;
  const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
  const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};
  int ret = 0;
  for (int i = 0; i < 8; ++i) {
    char x = s[0] + dx[i];
    char y = s[1] + dy[i];
    if (x >= 'a' && x <= 'h' && y >= '1' && y <= '8') ++ret;
  }
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}

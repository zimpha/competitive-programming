#include <bits/stdc++.h>

void run() {
  int n, m;
  std::cin >> n >> m;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::string s;
      std::cin >> s;
      if (s[0] == 'G' || s[0] == 'B' || s[0] == 'W') ++cnt;
    }
  }
  if (cnt == n * m) puts("#Black&White");
  else puts("#Color");
}

int main() {
  run();
  return 0;
}

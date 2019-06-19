#include <cstdio>
#include <iostream>
#include <string>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::string s;
    std::cin >> s;
    int b = 0, d = 0;
    for (size_t i = 1; i < s.size(); ++i) {
      if (s[i] == 'B') ++b;
      else ++d;
    }
    if (d && b >= d) printf("Case #%d: Y\n", cas);
    else printf("Case #%d: N\n", cas);
  }
  return 0;
}

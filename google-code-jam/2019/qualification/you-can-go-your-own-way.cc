#include <cstdio>
#include <string>
#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::string s, t;
    int n;
    std::cin >> n >> s;
    if (s[0] == s.back()) {
      int a = 0, b = 0;
      for (size_t i = 0; i + 1 < s.size(); ++i) {
        if (s[i] == s[0]) ++a;
        else ++b;
        if (s[i] != s[0] && s[i + 1] != s[0]) {
          break;
        }
      }
      for (int i = 0; i < b; ++i) t.push_back("ES"[s[0] == 'E']);
      for (int i = 0; i < a; ++i) t.push_back("ES"[s[0] == 'S']);
      for (int i = 0; i < n - 1 - a; ++i) t.push_back("ES"[s[0] == 'S']);
      for (int i = 0; i < n - 1 - b; ++i) t.push_back("ES"[s[0] == 'E']);
    } else {
      for (int i = 0; i < n - 1; ++i) t.push_back(s.back());
      for (int i = 0; i < n - 1; ++i) t.push_back(s[0]);
    }
    printf("Case #%d: %s\n", cas, t.c_str());
  }
  return 0;
}

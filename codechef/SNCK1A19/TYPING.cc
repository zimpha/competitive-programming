#include <cstdio>
#include <set>
#include <string>
#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    std::set<std::string> as;
    std::cin >> n;
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      int now = 2;
      for (int j = 1; j < s.size(); ++j) {
        if (s[j] == s[j - 1] || (s[j] == 'd' && s[j - 1] == 'f') || (s[j] == 'f' && s[j - 1] == 'd') || (s[j] == 'j' && s[j - 1] == 'k') || (s[j] == 'k' && s[j - 1] == 'j')) now += 4;
        else now += 2;
      }
      if (as.count(s)) ret += now / 2;
      else ret += now;
      as.insert(s);
    }
    printf("%d\n", ret);
  }
  return 0;
}

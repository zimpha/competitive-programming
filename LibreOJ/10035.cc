#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  for (std::string s; std::cin >> s; ) {
    if (s == ".") break;
    std::vector<int> fail(s.size(), -1);
    for (size_t i = 1; i < s.size(); ++i) {
      int &j = fail[i];
      for (j = fail[i - 1]; j >= 0 && s[j + 1] != s[i]; j = fail[j]);
      if (s[j + 1] == s[i]) ++j;
    }
    int p = s.size() - fail.back() - 1;
    if (s.size() % p) puts("1");
    else printf("%d\n", (int)s.size() / p);
  }
  return 0;
}

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s, t;
  std::cin >> s >> t;
  std::vector<int> fail(t.size(), -1);
  for (size_t i = 1; i < t.size(); ++i) {
    int &j = fail[i];
    for (j = fail[i - 1]; j >= 0 && t[j + 1] != t[i]; j = fail[j]);
    if (t[j + 1] == t[i]) ++j;
  }
  int ret = 0;
  for (int i = 0, j = -1; i < s.size(); ++i) {
    while (j >= 0 && t[j + 1] != s[i]) j = fail[j];
    if (t[j + 1] == s[i]) ++j;
    if (j == t.size() - 1) {
      j = fail[j];
      ++ret;
    }
  }
  printf("%d\n", ret);
  return 0;
}

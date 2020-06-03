#include <cstdio>
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::unordered_set<std::string> ss;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    ss.insert(s[i]);
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      std::string t(m, ' ');
      for (int k = 0; k < m; ++k) {
        if (s[i][k] == s[j][k]) t[k] = s[i][k];
        else t[k] = 'S' ^ 'E' ^ 'T' ^ s[i][k] ^ s[j][k];
      }
      ret += ss.count(t);
    }
  }
  printf("%d\n", ret / 3);
  return 0;
}

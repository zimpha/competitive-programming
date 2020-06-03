#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>

using int64 = long long;

int main() {
  std::string s[6];
  for (int i = 0; i < 6; ++i) std::cin >> s[i];
  for (int i = 1; i < 6; ++i) {
    if (s[i][0] == s[0][0] || s[i][1] == s[0][1]) {
      puts("YES");
      return 0;
    }
  }
  puts("NO");
  return 0;
}
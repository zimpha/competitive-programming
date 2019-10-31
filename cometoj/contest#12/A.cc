#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::string> s;
    for (int i = 0; i < n; ++i) {
      char buf[100];
      scanf("%s", buf);
      s.emplace_back(buf, buf + 3);
    }
    std::sort(s.begin(), s.end());
    bool valid = true;
    for (int i = 1; i < n; ++i) {
      if (s[i] == s[i - 1]) valid = false;
    }
    puts(valid ? "Yes" : "No");
  }
  return 0;
}

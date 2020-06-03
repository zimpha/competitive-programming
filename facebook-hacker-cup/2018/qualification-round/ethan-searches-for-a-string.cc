#include <cstdio>
#include <cstring>
#include <string>

const int N = 2000 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    std::string ret = "Impossible";
    for (int len = 1; len <= n; ++len) {
      bool valid = true;
      for (int i = 0; i + len < n; ++i) {
        if (s[i] != s[i + len]) valid = false;
      }
      if (!valid) continue;
      bool same = false;
      int p = -1;
      for (int i = 1; i < len; ++i) {
        if (s[i] == s[0]) {
          if (!same) p = i;
          same = true;
        }
      }
      if (!same) break;
      ret = "";
      for (int i = 0; i < p; ++i) ret += s[i];
      ret += s;
      break;
    }
    printf("Case #%d: %s\n", cas, ret.c_str());
  }
  return 0;
}

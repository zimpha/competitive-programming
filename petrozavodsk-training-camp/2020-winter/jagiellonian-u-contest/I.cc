#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

char s[N], t[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    std::reverse(s, s + n);
    for (int i = 0; i < n; ++i) s[i] -= '0';
    std::vector<std::string> ret;
    while (n > 2) {
      for (int i = n / 2; i < n; ++i) t[i] = s[i];
      --t[n / 2];
      for (int i = n / 2; i < n; ++i) {
        if (t[i] < 0) t[i] += 10, --t[i + 1];
        else break;
      }
      for (int i = n / 2 - 1; i >= 0; --i) {
        t[i] = t[n - 1 - i];
      }
      if (t[0] == 0) t[0] = 9;
      for (int i = 0; i < n; ++i) {
        if (s[i] < t[i]) s[i] += 10, --s[i + 1];
        s[i] -= t[i];
      }
      int m = n;
      while (m > 1 && t[m - 1] == 0) --m;
      for (int i = 0; i < m; ++i) t[i] += '0';
      t[m] = 0;
      std::reverse(t, t + m);
      ret.push_back(t);
      while (n > 1 && s[n - 1] == 0) --n;
    }
    if (n == 1) {
      if (s[0]) ret.push_back(std::to_string(s[0]));
    } else {
      int u = s[0] + s[1] * 10;
      int v = s[1] + s[1] * 10;
      if (v <= u) {
        ret.push_back(std::to_string(v));
        if (u - v) ret.push_back(std::to_string(u - v));
      } else if (s[1] == 1) {
        ret.push_back(std::to_string(9));
        ret.push_back(std::to_string(u - 9));
      } else {
        ret.push_back(std::to_string(v - 11));
        u -= v - 11;
        if (u == 10) ret.push_back(std::to_string(1)), --u;
        ret.push_back(std::to_string(u));
      }
    }
    printf("%d\n", (int)ret.size());
    for (auto &e: ret) puts(e.c_str());
  }
  return 0;
}

#include <cstdio>
#include <iostream>

using int64 = long long;

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int D;
    std::string s;
    std::cin >> D >> s;

    auto cost = [](const std::string &s) {
      int64 ret = 0, now = 1;
      for (auto &&c: s) {
        if (c == 'S') ret += now;
        else now *= 2;
      }
      return ret;
    };
    
    int ret = 0;
    while (cost(s) > D) {
      bool find = false;
      for (int i = s.size() - 1; i > 0; --i) {
        if (s[i] == 'S' && s[i - 1] == 'C') {
          std::swap(s[i], s[i - 1]);
          find = true;
          break;
        }
      }
      ++ret;
      if (!find) {
        ret = -1;
        break;
      }
    }
    if (ret != -1) printf("Case #%d: %d\n", cas, ret);
    else printf("Case #%d: IMPOSSIBLE\n", cas);
  }
  return 0;
}

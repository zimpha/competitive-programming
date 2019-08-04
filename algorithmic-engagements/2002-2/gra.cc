#include <cstdio>
#include <string>
#include <vector>

const int N = 1e5 + 10;

int main() {
  std::vector<std::string> fib = {"a", "b"};
  std::vector<std::vector<int>> fail;
  for (int i = 2; fib.back().size() < 100000; ++i) {
    fib.emplace_back(fib[i - 2] + fib[i - 1]);
  }
  for (auto &s: fib) {
    fail.emplace_back(s.size(), -1);
    auto& f = fail.back();
    for (int i = 1, j = -1; i < (int)s.size(); ++i) {
      while (j > 0 && s[j + 1] != s[i]) j = f[j];
      f[i] = s[j + 1] == s[i] ? ++j : j;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1, n; cas <= T; ++cas) {
    static char s[N];
    scanf("%d %s", &n, s);
    int m = 0;
    while (m < fib.size() && fib[m].size() <= n) ++m;
    std::vector<int> p(m, -1);
    std::vector<int> dp(n + 1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        while (p[j] > 0 && fib[j][p[j] + 1] != s[i]) p[j] = fail[j][p[j]];
        if (fib[j][p[j] + 1] == s[i]) ++p[j];
        if (p[j] == fib[j].size() - 1) {
          if (!dp[i + 1 - fib[j].size()]) dp[i + 1] = 1;
          p[j] = fail[j][p[j]];
        }
      }
    }
    if (dp[n]) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

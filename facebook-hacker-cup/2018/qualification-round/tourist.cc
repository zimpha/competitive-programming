#include <cstdio>
#include <vector>
#include <string>

using int64 = long long;

int64 binom[60][60];

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < 60; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
  }
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    int64 v;
    scanf("%d%d%lld", &n, &k, &v);
    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
      static char buf[100];
      scanf("%s", buf);
      s[i] = buf;
    }
    v = (v - 1) % binom[n][k] + 1;
    std::vector<std::string> res;
    for (int i = 0; i < n; ++i) {
      int need = k - res.size();
      if (need == 0) break;
      if (binom[n - i - 1][need - 1] >= v) {
        res.emplace_back(s[i]);
      } else {
        v -= binom[n - i - 1][need - 1];
      }
    }
    printf("Case #%d:", cas);
    for (auto &&s: res) printf(" %s", s.c_str());
    puts("");
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <cstring>

using int64 = long long;

const int64 mod = 4207849484;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    static char s[10000];
    int m;
    scanf("%d%s", &m, s);
    int n = strlen(s);
    std::vector<int64> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) if (s[i] != '0') {
      dp[i] %= mod;
      int u = 0;
      for (int j = 0; j < 3 && i + j < n; ++j) {
        u = u * 10 + s[i + j] - '0';
        if (1 <= u && u <= m) dp[i + j + 1] += dp[i];
      }
    }
    printf("Case #%d: %lld\n", cas, dp[n] % mod);
  }
  return 0;
}

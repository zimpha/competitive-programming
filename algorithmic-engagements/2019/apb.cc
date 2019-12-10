#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 100;

using int64 = long long;

int64 dp[N][2];
char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  dp[0][1] = 1;
  for (int i = 0; i < n; ++i) {
    for (int e = 0; e < 2; ++e) if (dp[i][e]) {
      int sum = s[i] - '0';
      for (int a = 0; a <= sum; ++a) {
        int b = sum - a;
        if (e && a <= b) dp[i + 1][e & (a == b)] += dp[i][e];
        if (!e) dp[i + 1][e] += dp[i][e];
      }
      if (i + 1 < n && s[i] == '1') {
        int sum = 10 + s[i + 1] - '0';
        for (int a = 0; a <= sum && a < 10; ++a) {
          int b = sum - a;
          if (b >= 10) continue;
          if (e && a <= b) {
            dp[i + 2][e & (a == b)] += dp[i][e];
          }
          if (!e) dp[i + 2][e] += dp[i][e];
        }
      }
    }
  }
  printf("%lld\n", dp[n][0] * 2 + dp[n][1]);
  return 0;
}

#include <cstdio>
#include <cstring>

const int N = 1e6 + 10;
const int mod = 1e9 + 7;

using int64 = long long;

char L[N], R[N];
int64 dp[N][11][2];
int small[N], odd[N];
int cnt[10];

int64 solve(char *s) {
  int n = strlen(s + 1);
  for (int i = 0; i <= n + 1; ++i) {
    memset(dp[i], 0, sizeof(dp[i]));
  }
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) {
    small[i] = odd[i] = 0;
    for (int x = 0; x < s[i] - '0'; ++x) small[i] += cnt[x];
    cnt[s[i] - '0'] ^= 1;
    for (int x = 0; x < 10; ++x) odd[i] += cnt[x];
  }
  dp[n + 1][0][0] = dp[n + 1][1][0] = 1;
  dp[n + 1][0][1] = dp[n + 1][1][1] = 1;
  for (int i = n; i >= 1; --i) {
    int o = s[i] - '0';
    dp[i][odd[i - 1]][0] = dp[i + 1][odd[i]][0];
    if (small[i]) dp[i][odd[i - 1]][0] += small[i] * dp[i + 1][odd[i - 1] - 1][1];
    if (o - small[i]) dp[i][odd[i - 1]][0] += (o - small[i]) * dp[i + 1][odd[i - 1] + 1][1];
    dp[i][odd[i - 1]][0] %= mod;
    for (int j = 0; j <= 10; ++j) {
      if (j < 10) dp[i][j][1] += dp[i + 1][j + 1][1] * (10 - j);
      if (j) dp[i][j][1] += dp[i + 1][j - 1][1] * j;
      dp[i][j][1] %= mod;
    }
  }
  int64 ret = dp[2][1][0] + (s[1] - '0' - 1) * dp[2][1][1];
  for (int i = 1; i < n; ++i) ret += 9 * dp[n + 2 - i][1][1];
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", L + 1, R + 1);
    int64 ret = solve(R) - solve(L);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; L[i]; ++i) cnt[L[i] - '0'] ^= 1;
    int sum = 0;
    for (int i = 0; i < 10; ++i) sum += cnt[i];
    ret += sum <= 1;
    ret %= mod; ret += mod; ret %= mod;
    printf("%lld\n", ret);
  }
  return 0;
}

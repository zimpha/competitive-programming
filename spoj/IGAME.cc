#include <cstdio>
#include <cstring>

using int64 = long long;
int64 dp[22][16][2];
char s[30];

int64 dfs(int d, int v, int e) {
  if (d == 20) return v == 0;
  if (dp[d][v][e] != -1) return dp[d][v][e];
  int u = e ? s[d] - '0' : 9;
  int64 &ret = dp[d][v][e];
  ret = 0;
  for (int o = 0; o <= u; ++o) {
    ret += dfs(d + 1, v ^ o, e && (o == u));
  }
  return ret;
}

int64 calc(int64 n) {
  memset(dp, -1, sizeof(dp));
  sprintf(s, "%020lld\n", n);
  return dfs(0, 0, 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 a, b;
    scanf("%lld%lld", &a, &b);
    int64 bob = calc(b) - calc(a - 1);
    printf("%lld %lld\n", b - a + 1 - bob, bob);
  }
  return 0;
}

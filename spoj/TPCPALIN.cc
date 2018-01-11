#include <cstdio>
#include <cstring>

constexpr int N = 500 + 10, mod = 3210121;

int dp[2][N][N];
char s[N], t[N];

int main() {
  scanf("%s %s", s + 1, t + 1);
  int sn = strlen(s + 1);
  int tn = strlen(t + 1);
  int h = (sn + tn) >> 1;
  for (int x = 0; x <= h; ++x) {
    for (int y = 0; y <= h; ++y) {
      dp[0][x][y] = 1;
    }
  }
  int f = 0;
  for (int L = h - 1; L >= 0; --L, f ^= 1) {
    for (int x = 0; x <= L; ++x) {
      int sf = x + 1;
      int tf = L - x + 1;
      for (int y = 0; y <= L; ++y) {
        int r = 0;        
        int st = sn - y;
        int tt = tn - (L - y);
        if (sf < st && s[sf] == s[st]) r += dp[f][x + 1][y + 1];
        if (tf < tt && t[tf] == t[tt]) r += dp[f][x][y];
        if (sf <= st && tf <= tt) {
          if (s[sf] == t[tt]) r += dp[f][x + 1][y];
          if (t[tf] == s[st]) r += dp[f][x][y + 1];
        }
        dp[f ^ 1][x][y] = r % mod;
      }
    }
  }
  int ans = dp[f][0][0];
  printf("%d\n", ans);
  return 0;
}

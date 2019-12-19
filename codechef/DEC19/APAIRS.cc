#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 20, mod = 1e9 + 7;

using int64 = long long;

char L[N], R[N];
int pos, digit;
int64 dp[N][N][N][2][2];
int64 cnt[N][10];

int64 solve(int d, int x, int y, int el, int er) {
  if (d == 19) return x <= pos && pos < 19 - y;
  int64 &ret = dp[d][x][y][el][er];
  if (ret != -1) return ret;
  ret = 0;
  int lo = L[d] - '0', ro = R[d] - '0';;
  int l = el ? lo : 0, r = er ? ro : 9;
  for (int o = l; o <= r; ++o) {
    ret += solve(d + 1, x + (o < digit), y + (o > digit), el & (o == lo), er & (o == ro));
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", L, R);
    int n = strlen(L);
    int m = strlen(R);
    std::reverse(L, L + n);
    for (int i = n; i < 19; ++i) L[i] = '0';
    std::reverse(R, R + m);
    for (int i = m; i < 19; ++i) R[i] = '0';
    std::reverse(L, L + 19);
    std::reverse(R, R + 19);
    for (pos = 0; pos < 19; ++pos) {
      for (digit = 0; digit < 10; ++digit) {
        memset(dp, -1, sizeof(dp));
        cnt[pos][digit] = solve(0, 0, 0, 1, 1) % mod;
      }
    }
    int64 ret = 0;
    for (int i = 0; i < 19; ++i) {
      for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
          ret += cnt[i][x] * cnt[i][y] % mod * std::abs(x - y);
        }
      }
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}

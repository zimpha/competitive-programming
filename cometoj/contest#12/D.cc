#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;

int64 dp[64][2][2][2][2];
int64 xs, ys, n, m, lm, rm;

int64 solve(int d, int ex, int ey, int el, int er) {
  if (d < 0) {
    int olm = lm & 1, orm = rm & 1;
    if (el && er) return olm <= 0 && 0 <= orm;
    if (el) return olm <= 0;
    if (er) return orm >= 0;
    return 1;
  }
  if (dp[d][ex][ey][el][er] != -1) return dp[d][ex][ey][el][er];
  int64 ret = 0;
  int ox = ex ? xs >> d & 1 : 1;
  int oy = ey ? ys >> d & 1 : 1;
  int on = n >> d & 1;
  int olm = el ? lm >> (d + 1) & 1 : 0;
  int orm = er ? rm >> (d + 1) & 1 : 1;
  for (int x = 0; x <= ox; ++x) {
    for (int y = 0; y <= oy; ++y) {
      if ((x ^ y) != on) continue;
      if (x == y && olm <= 0 && 0 <= orm) {
        ret += solve(d - 1, ex & (x == ox), ey & (y == oy), el & (0 == olm), er & (0 == orm));
      }
      if (x == 0 && y == 1 && olm <= 0 && 0 <= orm) {
        ret += solve(d - 1, ex & (x == ox), ey & (y == oy), el & (0 == olm), er & (0 == orm));
      }
      if (x == 1 && y == 0 && olm <= 1 && 1 <= orm) {
        ret += solve(d - 1, ex & (x == ox), ey & (y == oy), el & (1 == olm), er & (1 == orm));
      }
    }
  }
  return dp[d][ex][ey][el][er] = ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%lld%lld%lld%lld", &xs, &ys, &n, &m);
    lm = std::max<int64>(0, n - m);
    rm = n + m;
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", solve(62, 1, 1, 1, 1));
  }
  return 0;
}

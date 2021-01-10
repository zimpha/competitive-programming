#include <cstdio>
#include <cstring>

using i64 = long long;

i64 dp[40][3][3][2][2][2];
int A, B, K, W;

i64 dfs(int d, int sxy, int syx, int ex, int ey, int exy) {
  if (sxy > 2) sxy = 2;
  if (syx > 2) syx = 2;
  if (d < 0) {
    return sxy >= 1 && syx >= 1;
  }
  i64 &ret = dp[d][sxy][syx][ex][ey][exy];
  if (ret != -1) return ret;
  sxy -= 1, syx -= 1;
  ret = 0;
  int ua = ex ? (A >> d & 1) : 1;
  int ub = ey ? (B >> d & 1) : 1;
  int uw = exy ? (W >> d & 1) : 1;
  for (int x = 0; x <= ua; ++x) {
    for (int y = 0; y <= ub; ++y) {
      if ((x ^ y) > uw) continue;
      int t_sxy = sxy * 2 + x - y + (K >> d & 1);
      int t_syx = syx * 2 + y - x + (K >> d & 1);
      if (t_sxy < -1 || t_syx < -1) continue;
      ret += dfs(d - 1, t_sxy + 1, t_syx + 1, ex && (x == ua), ey && (y == ub), exy && ((x ^ y) == uw));
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%d%d", &A, &B, &K, &W);
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", dfs(31, 1, 1, 1, 1, 1));
  }
  return 0;
}

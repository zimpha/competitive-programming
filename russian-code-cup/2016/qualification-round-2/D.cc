#include <cstdio>
#include <cstring>

const int N = 13;

int rk[3][N], n;
int dp[1 << N][3];

int solve(int rest, int turn) {
  if (dp[rest][turn] != -1) return dp[rest][turn];
  if (__builtin_popcount(rest) == 1) {
    for (int i = 0; i < n; ++i) {
      if (rest >> i & 1) return i;
    }
  }
  int ret = -1;
  for (int i = 0; i < n; ++i) {
    if (rest >> i & 1) {
      int v = solve(rest ^ (1 << i), (turn + 1) % 3);
      if (ret == -1 || rk[turn][v] < rk[turn][ret]) ret = v;
    }
  }
  return dp[rest][turn] = ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < n; ++j) {
        int x;
        scanf("%d", &x);
        rk[i][x - 1] = j;
      }
    }
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve((1 << n) - 1, 0) + 1);
  }
  return 0;
}

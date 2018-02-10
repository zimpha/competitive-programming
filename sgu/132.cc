#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100, M = 1 << 7;

int board[N];
int dp[2][M][M];
int n, m;

void update(int &x, int y) {
  if (x == -1) x = y;
  else if (y != -1 && y < x) x = y;
}

void expand(int line, int p, int prev1, int prev2, int now1, int now2, int cost) {
  if (p > 0 && (~prev1 >> (p - 1) & 1) && (~now1 >> (p - 1) & 1)) return;
  if (p > 1 && (~now1 >> (p - 1) & 1) && (~now1 >> (p - 2) & 1)) return;
  if (p == m) {
    update(dp[line][now1][now2], cost);
    return;
  }
  expand(line, p + 1, prev1, prev2, now1, now2, cost);
  if ((~now1 >> p & 1) && (~now2 >> p & 1)) {
    expand(line, p + 1, prev1, prev2, now1 | (1 << p), now2 | (1 << p), cost + 1);
  }
  if (p + 1 < m && (~now1 >> p & 1) && (~now1 >> (p + 1) & 1)) {
    expand(line, p + 1, prev1, prev2, now1 | (1 << p) | (1 << p + 1), now2, cost + 1);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    char buf[10];
    scanf("%s", buf);
    board[i] = 0;
    for (int j = 0; j < m; ++j) {
      if (buf[j] == '*') board[i] |= 1 << j;
    }
  }
  memset(dp, -1, sizeof(dp));
  int s = 1 << m;
  dp[0][s - 1][board[0]] = 0;
  for (int i = 0; i < n; ++i) {
    memset(dp[(i & 1) ^ 1], -1, sizeof(dp[0]));
    for (int mask1 = 0; mask1 < s; ++mask1) {
      for (int mask2 = 0; mask2 < s; ++mask2) {
        if (dp[i & 1][mask1][mask2] == -1) continue;
        expand((i & 1) ^ 1, 0, mask1, mask2, mask2, board[i + 1], dp[i & 1][mask1][mask2]);
      }
    }
  }
  int ret = -1;
  for (int i = 0; i < s; ++i) {
    update(ret, dp[n & 1][i][0]);
  }
  printf("%d\n", ret);
  return 0;
}

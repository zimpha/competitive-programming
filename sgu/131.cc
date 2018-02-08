#include <cstdio>

using int64 = long long;

int64 dp[20][1 << 10];
int n, m;

void expand(int i, int b, int now, int pre) {
  if (b == m) {
    dp[i][now] += dp[i - 1][pre];
    return;
  }
  if (pre >> b & 1) expand(i, b + 1, now, pre);
  else {
    if (~now >> b & 1) {
      expand(i, b + 1, now | (1 << b), pre);
    }
    if (b + 1 < m && (~pre >> (b + 1) & 1)) {
      expand(i, b + 2, now, pre);
    }
    if (b && (~now >> (b - 1) & 1) && (~now >> b & 1)) {
      expand(i, b + 1, now | (1 << b - 1) | (1 << b), pre);
    }
  }
  // corner
  if (b + 1 < m) {
    int x = pre >> b & 1, y = pre >> (b + 1) & 1;
    if (x == 0 && (~now >> b & 1)) {
      expand(i, b + 1, now | (1 << b) | (1 << b + 1), pre);
    }
    if (x == 0 && y == 0) {
      if (~now >> b & 1) {
        expand(i, b + 2, now | (1 << b), pre);
      }
      expand(i, b + 2, now | (1 << (b + 1)), pre);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (1 << m); ++j) {
      if (dp[i][j]) {
        expand(i + 1, 0, 0, j);
      }
    }
  }
  printf("%lld\n", dp[n][0]);
  return 0;
}

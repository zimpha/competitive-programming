#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 510;

int dp[N][N][N];
int C[N], A[N], V[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &C[i], &A[i], &V[i]);
  }
  auto valid = [&](int x, int y) {
    return x == 0 || y == 0 || C[x] == C[y] || A[x] == A[y];
  };

  auto update = [&](int &x, int y) {
    if (x < y) x = y;
  };

  memset(dp, -1, sizeof(dp));
  dp[1][2][0] = 0;
  for (int first = 0; first <= n + 1; ++first) {
    for (int second = 0; second <= n + 1; ++second) {
      for (int last = 0; last <= n; ++last) {
        int now = dp[first][second][last];
        if (now == -1) continue;
        int third = std::min(n + 1, std::max({first, second, last}) + 1);
        if (first <= n && valid(last, first)) {
          update(dp[second][third][first], now + V[first]);
        }
        if (third <= n && valid(last, third)) {
          update(dp[first][second][third], now + V[third]);
        }
      }
    }
  }
  int ret = 0;
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      ret = std::max(ret, *std::max_element(dp[i][j], dp[i][j] + n + 1));
    }
  }
  printf("%d\n", ret);
  return 0;
}

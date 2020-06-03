#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 200, M = 1001;

int cost[N][N], loc[M];
int dp[2][N][N];
unsigned char from[M][N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &cost[i][j]);
    }
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &loc[i]);
    --loc[i];
  }
  memset(dp, -1, sizeof(dp));
  dp[0][1][2] = 0;
  for (int i = 0; i < m; ++i) {
    int u = i & 1, v = u ^ 1, z = loc[i];
    memset(dp[v], -1, sizeof(dp[v]));
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        if (dp[u][x][y] == -1) continue;
        int w = dp[u][x][y];
        // x -> loc[i + 1]
        if (y != loc[i + 1] && z != loc[i + 1]) {
          if (dp[v][z][y] == -1 || dp[v][z][y] > w + cost[x][loc[i + 1]]) {
            dp[v][z][y] = w + cost[x][loc[i + 1]];
            from[i + 1][z][y] = x;
          }
        }
        // y -> loc[i + 1]
        if (x != loc[i + 1] && z != loc[i + 1]) {
          if (dp[v][x][z] == -1 || dp[v][x][z] > w + cost[y][loc[i + 1]]) {
            dp[v][x][z] = w + cost[y][loc[i + 1]];
            from[i + 1][x][z] = y;
          }
        }
        // loc[i] -> loc[i + 1]
        if (x != loc[i + 1] && y != loc[i + 1]) {
          if (dp[v][x][y] == -1 || dp[v][x][y] > w + cost[loc[i]][loc[i + 1]]) {
            dp[v][x][y] = w + cost[loc[i]][loc[i + 1]];
            from[i + 1][x][y] = z;
          }
        }
      }
    }
  }
  int ret = -1, p = -1, q = -1;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      if (dp[m & 1][x][y] == -1) continue;
      if (ret == -1 || dp[m & 1][x][y] < ret) {
        p = x, q = y;
        ret = dp[m & 1][x][y];
      }
    }
  }
  printf("%d\n", ret);
  std::vector<int> step;
  for (int i = m; i >= 1; --i) {
    int r = from[i][p][q];
    if (loc[i - 1] == p) {
      p = r;
    } if (loc[i - 1] == q) {
      q = r;
    } else {
    }
    step.push_back(r);
  }
  std::reverse(step.begin(), step.end());
  int a = 0, b = 1, c = 2;
  for (int i = 0; i < m; ++i) {
    if (i) putchar(' ');
    if (a == step[i]) putchar('1'), a = loc[i + 1];
    else if (b == step[i]) putchar('2'), b = loc[i + 1];
    else if (c == step[i]) putchar('3'), c = loc[i + 1];
  }
  puts("");
  return 0;
}

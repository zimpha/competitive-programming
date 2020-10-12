#include <cstdio>
#include <algorithm>

const int N = 2e3 + 10;

char grid[N][N];
int dp[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", grid[i]);
    for (int j = 0; j < m; ++j) {
      dp[i][j] = -1;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0, k; j < m; ) {
      if (grid[i][j] == '@') ++j;
      else {
        int cnt = 0, found = 0, best = -1;
        for (k = j; k < m && grid[i][k] != '@'; ++k) {
          cnt += grid[i][k] == 'm';
          found |= grid[i][k] == 'S';
          if (i) best = std::max(best, dp[i - 1][k]);
        }
        if (found) {
          for (; j < k; ++j) dp[i][j] = cnt;
        } else if (best != -1) {
          for (; j < k; ++j) dp[i][j] = cnt + best;
        } else {
          j = k;
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'E') printf("%d\n", dp[i][j]);
    }
  }
  return 0;
}

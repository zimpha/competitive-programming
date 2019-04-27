#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

const int N = 40 + 10, M = 2000 + 10;

char s[N][M];
int dp[N][M], l[N];
char x[M], y[M];

int main() {
  int n, lx, ly;
  scanf("%d", &n);
  scanf("%d%s", &lx, x);
  scanf("%d%s", &ly, y);
  if (strcmp(x, y) == 0) {
    puts("0");
    return 0;
  }
  if (lx > ly) {
    std::swap(lx, ly);
    for (int i = 0; i < ly; ++i) std::swap(x[i], y[i]);
  }
  for (int i = 0; i < lx; ++i) {
    if (x[i] != y[i]) {
      puts("NIE");
      return 0;
    }
  }
  std::queue<std::pair<int, int>> queue;
  for (int i = 0; i < n; ++i) {
    scanf("%d%s", &l[i], s[i]);
    for (int j = 0; j < l[i]; ++j) dp[i][j] = -1;
    dp[i][l[i] - 1] = 1;
    queue.emplace(i, l[i] - 1);
  }
  while (!queue.empty()) {
    int x = queue.front().first;
    int y = queue.front().second;
    queue.pop();
    for (int i = 0; i < n; ++i) if (l[i] != y + 1) {
      int len = std::min(y + 1, l[i]);
      bool valid = true;
      for (int j = 0; j < len && valid; ++j) {
        if (s[i][l[i] - 1 - j] != s[x][y - j]) valid = false;
      }
      if (!valid) continue;
      int nx = x, ny = y;
      if (l[i] < y + 1) nx = x, ny = y - l[i];
      else nx = i, ny = l[i] - (y + 1) - 1;
      if (dp[nx][ny] == -1) {
        dp[nx][ny] = dp[x][y] + 1;
        queue.emplace(nx, ny);
      }
    }
  }
  /*
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l[i]; ++j) printf("%d ", dp[i][j]);
    puts("");
  }*/
  std::vector<int> op(ly, -1);
  op[lx - 1] = 0;
  for (int i = lx - 1; i < ly; ++i) {
    for (int j = 0; j < n; ++j) if (i + l[j] < ly) {
      bool valid = true;
      for (int k = 0; k < l[j] && valid; ++k) valid &= y[i + 1 + k] == s[j][k];
      if (!valid) continue;
      if (op[i + l[j]] == -1 || op[i + l[j]] > op[i] + 1) op[i + l[j]] = op[i] + 1;
    }
  }
  int ret = op[ly - 1];
  for (int i = lx - 1; i < ly; ++i) if (op[i] != -1) {
    int rest = ly - i - 1;
    if (rest == 0) continue;
    for (int j = 0; j < n; ++j) if (rest <= l[j] && dp[j][rest - 1] != -1) {
      bool valid = true;
      for (int k = 0; k < rest && valid; ++k) valid &= y[i + 1 + k] == s[j][k];
      if (!valid) continue;
      if (ret == -1 || ret > op[i] + dp[j][rest - 1]) ret = op[i] + dp[j][rest - 1];
    }
  }
  if (ret == -1) puts("NIE");
  else printf("%d\n", ret);
  return 0;
}

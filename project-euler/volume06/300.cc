#include <bits/stdc++.h>

int vis[20][20];
int protein[15];

int dfs(int x, int y, int x1, int y1, int x2, int y2, int d) {
  if (x < x1) x1 = x;
  if (x > x2) x2 = x;
  if (y < y1) y1 = y;
  if (y > y2) y2 = y;
  if (x2 - x1 >= 6 || y2 - y1 >= 6) return 0;
  int ret = 0;
  if (++d == 15) {
    for (int i = x1; i <= x2; ++i) {
      for (int j = y1; j <= y2; ++j) {
        if (vis[i][j] != 1) continue;
        if (i + 1 <= x2 && vis[i + 1][j] == 1) ++ret;
        if (j + 1 <= y2 && vis[i][j + 1] == 1) ++ret;
      }
    }
    return ret;
  }
  if (vis[x + 1][y] == -1) {
    vis[x + 1][y] = protein[d];
    ret = std::max(ret, dfs(x + 1, y, x1, y1, x2, y2, d));
    vis[x + 1][y] = -1;
  }
  if (vis[x - 1][y] == -1 && d >= 2) {
    vis[x - 1][y] = protein[d];
    ret = std::max(ret, dfs(x - 1, y, x1, y1, x2, y2, d));
    vis[x - 1][y] = -1;
  }
  if (vis[x][y + 1] == -1 && d >= 2) {
    vis[x][y + 1] = protein[d];
    ret = std::max(ret, dfs(x, y + 1, x1, y1, x2, y2, d));
    vis[x][y + 1] = -1;
  }
  if (vis[x][y - 1] == -1 && d >= 3) {
    vis[x][y - 1] = protein[d];
    ret = std::max(ret, dfs(x, y - 1, x1, y1, x2, y2, d));
    vis[x][y - 1] = -1;
  }
  return ret;
}

long run(int n) {
  long ret = 0;
  memset(vis, -1, sizeof(vis));
  for (int msk = 0; msk < (1 << n); ++msk) {
    if (msk % 1000 == 0) std::cout << ret << std::endl;
    for (int i = 0; i < n; ++i) {
      protein[i] = msk >> i & 1;
    }
    vis[10][10] = protein[0];
    ret += dfs(10, 10, 10, 10, 10, 10, 0);
    vis[10][10] = -1;
  }
  return ret;
}

int main() {
  std::cout << run(15) << std::endl;
  return 0;
}

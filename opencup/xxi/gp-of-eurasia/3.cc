#include <cstdio>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

const int N = 2e3 + 10;

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};

char grid[N][N];
pii from[N][N];
int dp[N][N];

int main() {
  int n, m, r, p;
  scanf("%d%d%d%d", &n, &m, &p, &r);
  int sx, sy, ex, ey;
  for (int i = 0; i < n; ++i) {
    scanf("%s", grid[i]);
    for (int j = 0; j < m; ++j) {
      dp[i][j] = -1;
      if (grid[i][j] == 'S') {
        sx = i;
        sy = j;
      }
      if (grid[i][j] == 'E') {
        ex = i;
        ey = j;
      }
    }
  }
  dp[sx][sy] = 0;
  std::vector<pii> queue = {{sx, sy}};
  for (int dis = 1; !queue.empty(); ++dis) {
    for (size_t i = 0; i < queue.size(); ++i) {
      int x = queue[i].first, y = queue[i].second;
      for (int k = 0; k < 4; ++k) {
        int xx = x + dx[k], yy = y + dy[k];
        if (xx < 0 || xx >= n || yy < 0 || yy >= m || dp[xx][yy] != -1) continue;
        if (grid[xx][yy] == '@') continue;
        dp[xx][yy] = dp[x][y];
        from[xx][yy] = {x, y};
        queue.emplace_back(xx, yy);
      }
    }
    // filter useless position
    std::vector<pii> tmp;
    for (size_t i = 0; i < queue.size(); ++i) {
      int x = queue[i].first, y = queue[i].second;
      bool found = false;
      for (int k = 0; k < 4; ++k) {
        int xx = x + dx[k], yy = y + dy[k];
        if (xx < 0 || xx >= n || yy < 0 || yy >= m || dp[xx][yy] != -1) continue;
        if (grid[xx][yy] == '@') found = true;
      }
      if (found) tmp.emplace_back(x, y);
    }
    queue = tmp;
    for (int it = 0; it < r && !queue.empty(); ++it) {
      std::vector<pii> tmp;
      for (size_t i = 0; i < queue.size(); ++i) {
        int x = queue[i].first, y = queue[i].second;
        for (int k = 0; k < 4; ++k) {
          int xx = x + dx[k], yy = y + dy[k];
          if (xx < 0 || xx >= n || yy < 0 || yy >= m || dp[xx][yy] != -1) continue;
          dp[xx][yy] = dis;
          from[xx][yy] = {x, y};
          tmp.emplace_back(xx, yy);
        }
      }
      queue.swap(tmp);
    }
    for (int it = 0; it < p / 2 && !queue.empty(); ++it) {
      std::vector<pii> tmp;
      for (size_t i = 0; i < queue.size(); ++i) {
        int x = queue[i].first, y = queue[i].second;
        for (int k = 0; k < 8; ++k) {
          int xx = x + dx[k], yy = y + dy[k];
          if (xx < 0 || xx >= n || yy < 0 || yy >= m || dp[xx][yy] != -1) continue;
          dp[xx][yy] = dis;
          from[xx][yy] = {x, y};
          tmp.emplace_back(xx, yy);
        }
      }
      queue.swap(tmp);
    }
  }
  printf("%d\n", dp[ex][ey]);
  std::vector<pii> order;
  while (ex != sx || ey != sy) {
    int nx = from[ex][ey].first;
    int ny = from[ex][ey].second;
    if (dp[nx][ny] < dp[ex][ey]) {
      order.emplace_back(nx + 1, ny + 1);
    }
    ex = nx;
    ey = ny;
  }
  std::reverse(order.begin(), order.end());
  for (auto &e: order) printf("%d %d\n", e.first, e.second);
  return 0;
}

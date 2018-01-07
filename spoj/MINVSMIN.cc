#include <cstdio>
#include <queue>
#include <functional>

using pii = std::pair<int, int>;
const int N = 1e3 + 10;

int d1[N][N], d2[N][N], n;
char g[N][N];

constexpr int dx[] = {0, 0, 1, -1};
constexpr int dy[] = {-1, 1, 0, 0};

void bfs(int x, int y, int dis[N][N]) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dis[i][j] = -1;
    }
  }
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    std::tie(x, y) = queue.front();
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= n || g[xx][yy] == 'B') continue;
      if (dis[xx][yy] == -1) {
        dis[xx][yy] = dis[x][y] + 1;
        queue.emplace(xx, yy);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dis[i][j] == -1) dis[i][j] = 1e9;
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%s", g[i]);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (g[i][j] == 'X') bfs(i, j, d1);
        if (g[i][j] == 'Y') bfs(i, j, d2);
      }
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (g[i][j] == 'b') {
          if (d1[i][j] < d2[i][j]) ++ret;
          if (d1[i][j] > d2[i][j]) --ret;
        }
      }
    }
    if (ret > 0) puts("Pack 1");
    else if (ret < 0) puts("Pack 2");
    else puts("Gru gets to keep all bananas!");
  }
  return 0;
}

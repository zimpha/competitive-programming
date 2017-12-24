#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using pii = std::pair<int, int>;
int dis[5][8][8][8][8];

void solve_king(int x, int y, int dis[8][8]) {
  const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[8] = {-1, 0, 1, 1, -1, -1, 0, 1};
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    x = queue.front().first;
    y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 8; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) continue;
      if (dis[xx][yy] == -1) {
        dis[xx][yy] = dis[x][y] + 1;
        queue.emplace(xx, yy);
      }
    }
  }
}

void solve_knight(int x, int y, int dis[8][8]) {
  const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
  const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    x = queue.front().first;
    y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 8; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) continue;
      if (dis[xx][yy] == -1) {
        dis[xx][yy] = dis[x][y] + 1;
        queue.emplace(xx, yy);
      }
    }
  }
}

void solve_queen(int x, int y, int dis[8][8]) {
  const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[8] = {-1, 0, 1, 1, -1, -1, 0, 1};
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    x = queue.front().first;
    y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 8; ++i) {
      for (int j = 1; j < 8; ++j) {
        int xx = x + dx[i] * j, yy = y + dy[i] * j;
        if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) break;
        if (dis[xx][yy] == -1) {
          dis[xx][yy] = dis[x][y] + 1;
          queue.emplace(xx, yy);
        }
      }
    }
  }
}

void solve_tower(int x, int y, int dis[8][8]) {
  const int dx[4] = {1, -1, 0, 0};
  const int dy[4] = {0, 0, 1, -1};
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    x = queue.front().first;
    y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      for (int j = 1; j < 8; ++j) {
        int xx = x + dx[i] * j, yy = y + dy[i] * j;
        if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) break;
        if (dis[xx][yy] == -1) {
          dis[xx][yy] = dis[x][y] + 1;
          queue.emplace(xx, yy);
        }
      }
    }
  }
}

void solve_bishop(int x, int y, int dis[8][8]) {
  const int dx[4] = {-1, -1, 1, 1};
  const int dy[4] = {-1, 1, -1, 1};
  std::queue<pii> queue;
  queue.emplace(x, y);
  dis[x][y] = 0;
  while (!queue.empty()) {
    x = queue.front().first;
    y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      for (int j = 1; j < 8; ++j) {
        int xx = x + dx[i] * j, yy = y + dy[i] * j;
        if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) break;
        if (dis[xx][yy] == -1) {
          dis[xx][yy] = dis[x][y] + 1;
          queue.emplace(xx, yy);
        }
      }
    }
  }
}

void prepare() {
  memset(dis, -1, sizeof(dis));
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      solve_king(i, j, dis[0][i][j]);
      solve_knight(i, j, dis[1][i][j]);
      solve_queen(i, j, dis[2][i][j]);
      solve_tower(i, j, dis[3][i][j]);
      solve_bishop(i, j, dis[4][i][j]);
    }
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, x1, y1, x2, y2;
    scanf("%d%d%d%d%d%d", &a, &x1, &y1, &b, &x2, &y2);
    int ret = -1;
    for (int x = 0; x < 8; ++x) {
      for (int y = 0; y < 8; ++y) {
        if (dis[a][x1][y1][x][y] != -1 && dis[b][x2][y2][x][y] != -1) {
          int now = dis[a][x1][y1][x][y] + dis[b][x2][y2][x][y];
          if (ret == -1 || now < ret) ret = now;
        }
      }
    }
    if (ret == -1) puts("INF");
    else printf("%d\n", ret);
  }
  return 0;
}

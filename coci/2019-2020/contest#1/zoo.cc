#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

const int N = 1000 + 10;

std::vector<int> edges[N * N];
char s[N][N];
int idx[N][N];
int n, m;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

void fill(int x, int y, int col, char c) {
  std::queue<std::pair<int, int>> queue;
  queue.emplace(x, y);
  idx[x][y]= col;
  while (!queue.empty()) {
    std::tie(x, y) = queue.front();
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
      if (idx[xx][yy] != -1 || s[xx][yy] != c) continue;
      idx[xx][yy] = col;
      queue.emplace(xx, yy);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }
  memset(idx, -1, sizeof(idx));
  int nn = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (idx[i][j] != -1 || s[i][j] == '*') continue;
      fill(i, j, nn++, s[i][j]);
    }
  }
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (s[x][y] == '*') continue;
      for (int i = 0; i < 4; ++i) {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx >= 0 && xx < n && yy >= 0 && yy < m && idx[x][y] != idx[xx][yy] && idx[xx][yy] != -1) {
          edges[idx[x][y]].push_back(idx[xx][yy]);
        }
      }
    }
  }
  std::vector<int> dis(nn, -1);
  std::queue<int> queue;
  queue.push(0);
  dis[0] = 1;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto &v: edges[u]) if (dis[v] == -1) {
      dis[v] = dis[u] + 1;
      queue.push(v);
    }
  }
  printf("%d\n", *max_element(dis.begin(), dis.end()));
  return 0;
}

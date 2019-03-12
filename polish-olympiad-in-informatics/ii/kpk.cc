#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 100 + 10;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

struct Node {
  int x, y, d;
  int l;
};

char grid[N][N];
int dis[N][N][4];
int from[N][N][4];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", grid[i]);
  int x1, y1, x2, y2;
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  --x1, --y1, --x2, --y2;
  memset(dis, -1, sizeof(dis));
  std::vector<Node> queue;
  queue.push_back({x1, y1, -1, 0});
  int td = -1, tl = -1;
  for (size_t i = 0; i < queue.size(); ++i) {
    int x = queue[i].x, y = queue[i].y;
    int d = queue[i].d, l = queue[i].l;
    if (x == x2 && y == y2) {
      td = d, tl = l;
      break;
    }
    for (int k = 0; k < 4; ++k) {
      if (d != -1 && ((d + 2) % 4 == k || (d + 3) % 4 == k)) continue;
      int xx = x + dx[k], yy = y + dy[k];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
      if (dis[xx][yy][k] != -1) continue;
      if (grid[xx][yy] == '1') continue;
      dis[xx][yy][k] = l + 1;
      from[xx][yy][k] = i;
      queue.push_back({xx, yy, k, l + 1});
    }
  }
  if (td == -1) puts("NIE");
  else {
    printf("%d\n", tl + 1);
    std::vector<int> x, y;
    for (int i = 0; i <= tl; ++i) {
      x.push_back(x2);
      y.push_back(y2);
      int p = from[x2][y2][td];
      x2 = queue[p].x;
      y2 = queue[p].y;
      td = queue[p].d;
    }
    std::reverse(x.begin(), x.end());
    std::reverse(y.begin(), y.end());
    for (int i = 0; i <= tl; ++i) printf("%d %d\n", x[i] + 1, y[i] + 1);
  }
  return 0;
}

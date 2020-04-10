#include <cstdio>
#include <queue>
#include <algorithm>

const int N = 500 + 10;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

int dist[N][N];
char s[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; ++j) {
      dist[i][j] = -1;
    }
  }
  int q;
  scanf("%d", &q);
  std::priority_queue<std::pair<int, int>> pq;
  for (int i = 0; i < q; ++i) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    --x, --y;
    if (s[x][y] == '.') {
      if (dist[x][y] == -1 || dist[x][y] > t) {
        dist[x][y] = t;
        pq.emplace(-dist[x][y], x * m + y);
      }
    }
  }
  while (!pq.empty()) {
    int d = -pq.top().first;
    int x = pq.top().second / m;
    int y = pq.top().second % m;
    pq.pop();
    if (dist[x][y] < d) continue;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
      if (s[xx][yy] != '.') continue;
      if (dist[xx][yy] == -1 || dist[xx][yy] > dist[x][y] + 1) {
        dist[xx][yy] = dist[x][y] + 1;
        pq.emplace(-dist[xx][yy], xx * m + yy);
      }
    }
  }
  bool found = false;
  int ret = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (s[i][j] == '.') {
      if (dist[i][j] == -1) found = true;
      else ret = std::max(ret, dist[i][j]);
    }
  }
  if (found) puts("Impossible");
  else printf("%d\n", ret);
  return 0;
}

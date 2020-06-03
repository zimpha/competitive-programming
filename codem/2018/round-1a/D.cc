#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

const int N = 2e3 + 10;

bool go[N][N][4];
int dis[N][N], from[N][N];
int n, m, k;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct edge_t {
  int u, v, w;
  bool operator < (const edge_t &rhs) const {
    return w < rhs.w;
  }
};

using int64 = long long;

int dsu[N * N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    static char buf[N];
    scanf("%s", buf);
    for (int j = 0; j < m - 1; ++j) {
      if (buf[j] == '0') go[i][j][1] = go[i][j + 1][3] = 1;
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    static char buf[N];
    scanf("%s", buf);
    for (int j = 0; j < m; ++j) {
      if (buf[j] == '0') go[i][j][2] = go[i + 1][j][0] = 1;
    }
  }
  memset(dis, -1, sizeof(dis));
  std::queue<std::pair<int, int>> queue;
  for (int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    queue.emplace(x, y);
    dis[x][y] = 0;
    from[x][y] = i;
  }
  while (!queue.empty()) {
    int x = queue.front().first;
    int y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 4; ++i) if (go[x][y][i]) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx >= 0 && xx < n && yy >= 0 && yy < m && dis[xx][yy] == -1) {
        dis[xx][yy] = dis[x][y] + 1;
        from[xx][yy] = from[x][y];
        queue.emplace(xx, yy);
      }
    }
  }
  std::vector<edge_t> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < 4; ++k) if (go[i][j][k]) {
        int x = i + dx[k], y = j + dy[k];
        int u = from[i][j], v = from[x][y];
        if (u != v) {
          edges.push_back((edge_t){u, v, dis[i][j] + dis[x][y] + 1});
        }
      }
    }
  }
  std::sort(edges.begin(), edges.end());
  for (int i = 0; i < k; ++i) dsu[i] = i;
  int64 ret = 0;
  for (auto &&e : edges) {
    int u = get(e.u), v = get(e.v);
    if (u != v) {
      ret += e.w;
      dsu[u] = v;
    }
  }
  printf("%lld\n", ret);
  return 0;
}
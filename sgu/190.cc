#include <cstdio>
#include <vector>
#include <cstring>

const int N = 40, S = N * N;

bool mark[N][N];
std::vector<int> edges[S];
int mate[S], vis[S];

bool aug(int u) {
  for (auto &&v: edges[u]) if (!vis[v]) {
    vis[v] = true;
    if (mate[v] == -1 || aug(mate[v])) {
      mate[v] = u;
      mate[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(mark, 1, sizeof(mark));
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    mark[x - 1][y - 1] = 0;
  }
  const int dx[] = {0, 0, 1, -1};
  const int dy[] = {1, -1, 0, 0};
  int ls = 0, rs = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!mark[i][j]) continue;
      if ((i ^ j) & 1) {
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (x < 0 || x >= n || y < 0 || y >= n || !mark[x][y]) continue;
          edges[i * n + j].emplace_back(x * n + y);
        }
        ++ls;
      } else ++rs;
    }
  }
  memset(mate, -1, sizeof(mate));
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mark[i][j] && ((i ^ j) & 1)) {
        memset(vis, 0, sizeof(vis));
        if (aug(i * n + j)) ++ret;
      }
    }
  }
  if (ls != rs || ret != ls) puts("No");
  else {
    std::vector<std::pair<int, int>> ver, hor;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (((i ^ j) & 1) && mate[i * n + j] != -1) {
          int x = mate[i * n + j] / n, y = mate[i * n + j] % n;
          if (y == j) hor.emplace_back(i * n + j, x * n + j);
          else ver.emplace_back(i * n + j, x * n + y);
        }
      }
    }
    puts("Yes");
    printf("%d\n", (int)hor.size());
    for (auto &&e: hor) {
      printf("%d %d\n", std::min(e.first / n, e.second / n) + 1, e.first % n + 1);
    }
    printf("%d\n", (int)ver.size());
    for (auto &&e: ver) {
      printf("%d %d\n", e.first / n + 1, std::min(e.first % n, e.second % n) + 1);
    }
  }
  return 0;
}

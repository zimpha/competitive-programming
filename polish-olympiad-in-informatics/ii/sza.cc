#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 60;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int grid[N][N];
std::vector<int> edges[N * N];
bool mark[N * N];
int mate[N * N];

bool aug(int u) {
  for (auto &&v: edges[u]) if (!mark[v]) {
    mark[v] = 1;
    if (mate[v] == -1 || aug(mate[v])) {
      mate[v] = u;
      mate[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < 3; ++i) {
    int p;
    scanf("%d", &p);
    --p;
    grid[p / n][p % n] = 1;
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (grid[i][j] || (i ^ j) % 2 == 1) continue;
    for (int k = 0; k < 4; ++k) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 0 || x >= n || y < 0 || y >= n) continue;
      if (grid[x][y]) continue;
      edges[i * n + j].push_back(x * n + y);
    }
  }
  memset(mate, -1, sizeof(mate));
  int ret = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (grid[i][j] || (i ^ j) % 2 == 1) continue;
    memset(mark, 0, sizeof(mark));
    if (aug(i * n + j)) ++ret;
  }
  if (ret != (n * n - 3) / 2) puts("NIE");
  else {
    for (int i = 0; i < n * n; ++i) if (mate[i] != -1) {
      if (i < mate[i]) printf("%d %d\n", i + 1, mate[i] + 1);
    }
  }
  return 0;
}

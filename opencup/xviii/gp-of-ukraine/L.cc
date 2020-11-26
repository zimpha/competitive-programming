#include <cstdio>
#include <vector>

using i64 = long long;

const int N = 600, M = 1e6 + 10;

int grid[N][N], sum[N][N];
int x1[M], x2[M], y1[M], y2[M];
int rx[M], ry[M];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<bool> mark(M);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &grid[i][j]);
      int v = grid[i][j];
      if (!mark[v]) {
        mark[v] = true;
        x1[v] = x2[v] = i;
        y1[v] = y2[v] = j;
        rx[v] = i;
        ry[v] = j;
        sum[i][j]++;
      } else {
        x1[v] = std::min(x1[v], i);
        x2[v] = std::max(x2[v], i);
        y1[v] = std::min(y1[v], j);
        y2[v] = std::max(y2[v], j);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  }
  std::vector<bool> done(M);
  i64 ret = 0;

  auto check = [&](int u, int v) {
    if (done[v]) return;
    done[v] = true;
    if (x1[u] <= x1[v] && x2[v] <= x2[u] && y1[u] <= y1[v] && y2[v] <= y2[u]) return;
    ret -= x1[u] <= rx[v] && rx[v] <= x2[u] && y1[u] <= ry[v] && ry[v] <= y2[u];
  };

  for (int v = 0; v < M; ++v) if (mark[v]) {
    done[v] = true;
    ret += sum[x2[v]][y2[v]];
    ret -= sum[x2[v]][y1[v] - 1];
    ret -= sum[x1[v] - 1][y2[v]];
    ret += sum[x1[v] - 1][y1[v] - 1];
    ret -= 1;
    for (int i = x1[v]; i <= x2[v]; ++i) {
      check(v, grid[i][y1[v]]);
      check(v, grid[i][y2[v]]);
    }
    for (int i = y1[v]; i <= y2[v]; ++i) {
      check(v, grid[x1[v]][i]);
      check(v, grid[x2[v]][i]);
    }
    for (int i = x1[v]; i <= x2[v]; ++i) {
      done[grid[i][y1[v]]] = done[grid[i][y2[v]]] = false;
    }
    for (int i = y1[v]; i <= y2[v]; ++i) {
      done[grid[x1[v]][i]] = done[grid[x2[v]][i]] = false;
    }
    done[v] = false;
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 1000 + 10;

i64 dist[N][N], sum[N][N];
std::vector<std::pair<int, int>> edges[N];

void dfs(int root, int u, int d, int p = -1) {
  dist[root][u] = d;
  for (auto &e: edges[u]) if (e.first != p) {
    sum[root][d + 1] += e.second;
    dfs(root, e.first, d + 1, u);
  }
}

int u[N], v[N], d[N];

int main() {
  freopen("danger.in", "r", stdin);
  freopen("danger.out", "w", stdout);
  int n, q, m = 0;
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }
  for (int i = 0; i < n; ++i) {
    dfs(i, i, 0);
    for (int j = 1; j <= n; ++j) {
      sum[i][j] += sum[i][j - 1];
    }
  }

  for (int i = 0, op; i < q; ++i) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d%d", &u[m], &v[m], &d[m]);
      --u[m], --v[m];
      ++m;
    } else {
      int x, y;
      scanf("%d%d", &x, &y); --x;
      i64 ret = sum[x][y];
      for (int j = 0; j < m; ++j) {
        int d1 = dist[u[j]][v[j]];
        int d2 = dist[x][u[j]];
        int d3 = dist[x][v[j]];
        int c = (d3 - d1 + d2) / 2;
        int a = dist[x][u[j]] - c;
        int b = dist[x][v[j]] - c;
        if (c <= y) {
          int e = std::min(y - c, a) + std::min(y - c, b);
          ret += d[j] * e;
        }
      }
      printf("%lld\n", ret);
    }
  }
  return 0;
}

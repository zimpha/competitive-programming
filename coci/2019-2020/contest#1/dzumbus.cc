#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
 
using int64 = long long;
 
const int N = 1000 + 10;
const int64 inf = 1e15;
 
std::vector<int> edges[N];
int size[N], visited[N], cost[N];
int64 dp[N][N][2];
int n, m;
 
void update(int64 &x, int64 y) {
  if (x > y) x = y;
}
 
void dfs(int u, int p = -1) {
  visited[u] = 1;
  size[u] = 1;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    size[u] += size[v];
  }
  int s = 0;
  static int64 f0[N], g0[N], f1[N], g1[N];
  f0[0] = 0;
  f1[0] = inf;
  for (auto &v: edges[u]) if (v != p) {
    for (int i = 0; i <= s + size[v]; ++i) g0[i] = inf;
    for (int i = 0; i <= s + size[v]; ++i) g1[i] = inf;
    for (int i = 0; i <= s; ++i) {
      for (int j = 0; j <= size[v]; ++j) {
        update(g0[i + j], f0[i] + dp[v][j][0]);
        update(g0[i + j], f0[i] + dp[v][j][1]);
 
        update(g1[i + j], f1[i] + dp[v][j][0]);
        update(g1[i + j], f1[i] + dp[v][j][1]);
        update(g1[i + j], f0[i] + dp[v][j][1]);
        update(g1[i + j + 1], f1[i] + dp[v][j][0] + cost[v]);
        update(g1[i + j + 1], f0[i] + dp[v][j][0] + cost[v]);
      }
    }
    s += size[v];
    for (int i = 0; i <= s; ++i) f0[i] = g0[i];
    for (int i = 0; i <= s; ++i) f1[i] = g1[i];
  }
  for (int i = 0; i <= s + 1; ++i) {
    dp[u][i][0] = dp[u][i][1] = inf;
    if (i <= s) dp[u][i][0] = f0[i];
    if (i >= 2) dp[u][i][1] = f1[i - 1] + cost[u];
  }
}
 
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &cost[i]);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  std::vector<int> roots;
  for (int i = 0; i < n; ++i) if (!visited[i]) {
    dfs(i);
    roots.push_back(i);
  }
  std::vector<int64> best(n + 1, inf);
  int s = 0;
  best[0] = 0;
  for (auto &u: roots) {
    std::vector<int64> g(n + 1, inf);
    for (int i = 0; i <= s; ++i) {
      for (int j = 0; j <= size[u]; ++j) {
        update(g[i + j], best[i] + dp[u][j][0]);
        update(g[i + j], best[i] + dp[u][j][1]);
      }
    }
    s += size[u];
    best.swap(g);
  }
  best[1] = 0;
  for (int i = n - 1; i >= 0; --i) {
    best[i] = std::min(best[i], best[i + 1]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d", &s);
    int ret = std::upper_bound(best.begin(), best.end(), s) - best.begin() - 1;
    if (ret == 1) ret = 0;
    printf("%d\n", ret);
  }
  return 0;
}

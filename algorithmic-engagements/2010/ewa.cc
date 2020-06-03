#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

const int N = 1000 + 10, inf = 1e9;
int cap[N][N], lev[N], cur[N];
int g[N], f[N];
int G[N][N];
int n, m;

void bfs(int s, int dis[], int G[][N]) {
  for (int i = 0; i < n; ++ i) dis[i] = -1;
  std::queue<int> Q; Q.push(s); dis[s] = 0;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (int v = 0; v < n; ++ v) if (G[u][v]) {
      if (dis[v] == -1) dis[v] = dis[u] + 1, Q.push(v);
    }
  }
}

void build() {
  bfs(0, f, G);
  memset(cap, 0, sizeof(cap));
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
      if (G[i][j]) cap[j][i] = 1;
    }
  }
  bfs(n - 1, g, cap);
  memset(cap, 0, sizeof(cap));
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
      if (G[i][j] && f[i] + g[j] + 1 <= 3) {
        cap[i][j] = 1;
      }
    }
  }
}

namespace NT {
  bool bfs(int s, int t) {
    for (int i = 0; i < n; ++ i) lev[i] = -1;
    std::queue<int> Q; Q.push(s); lev[s] = 0;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      for (int v = 0; v < n; ++ v) {
        if (cap[u][v] > 0 && lev[v] == -1) {
          lev[v] = lev[u] + 1;
          Q.push(v);
        }
      }
    }
    return lev[t] != -1;
  }

  int dfs(int u, int t, int lim) {
    if (u == t) return lim;
    int ret = 0;
    for (int &v = cur[u]; v < n && ret < lim; ++ v) {
      if (lev[v] == lev[u] + 1 && cap[u][v] > 0) {
        int tmp = dfs(v, t, std::min(lim - ret, cap[u][v]));
        ret += tmp; cap[u][v] -= tmp; cap[v][u] += tmp;
      }
    }
    if (!ret) lev[u] = -1; return ret;
  }

  int dinic(int s, int t) {
    int ret = 0;
    while (bfs(s, t)) {
      memset(cur, 0, sizeof(cur[0]) * n);
      ret += dfs(s, t, inf);
    }
    return ret;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b; scanf("%d%d", &a, &b);
    G[a - 1][b - 1] = true;
  }
  build();
  printf("%d\n", NT::dinic(0, n - 1));
  return 0;
}

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 400 + 10, inf = 0x3f3f3f3f;

bool has[N][N];
int g[N][N], dis[N];
int n, m;

void sssp(int s) {
  std::vector<bool> mark(n);
  memcpy(dis, g[s], sizeof(g[s]));
  dis[s] = 0;
  mark[s] = true;
  for (int it = 0; it < n; ++it) {
    int u = -1;
    for (int i = 0; i < n; ++i) {
      if (!mark[i] && dis[i] != inf && (u == -1 || dis[i] < dis[u])) {
        u = i;
      }
    }
    if (u == -1) break;
    mark[u] = true;
    for (int v = 0; v < n; ++v) {
      if (!mark[v] && dis[v] > dis[u] + g[u][v]) {
        dis[v] = dis[u] + g[u][v];
      }
    }
  }
}

bool dinic_bfs(int s, int t) {
  memset(dis, -1, sizeof(dis));
  std::queue<int> queue;
  queue.push(s);
  dis[s] = 0;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (int v = 0; v < n; ++v) {
      if (g[u][v] > 0 && dis[v] == -1) {
        dis[v] = dis[u] + 1;
        queue.push(v);
      }
    }
  }
  return dis[t] != -1;
}

int aug(int u, int t, int upp) {
  if (u == t) return upp;
  for (int v = 0; v < n; ++v) {
    if (dis[v] == dis[u] + 1 && g[u][v] > 0) {
      int now = aug(v, t, std::min(upp, g[u][v]));
      if (now) {
        g[u][v] -= now;
        g[v][u] += now;
        return now;
      }
    }
  }
  dis[u] = -1;
  return 0;
}

int dinic(int s, int t) {
  int flow = 0;
  for (int i = 0; i < 2; ++i) {
    if (!dinic_bfs(s, t)) break;
    flow += aug(s, t, 1);
  }
  return flow;
}

bool output(int s, int t) {
  if (s == t) {
    printf("%d\n", s + 1);
    return true;
  } else {
    printf("%d ", s + 1);
  }
  for (int u = 0; u < n; ++u) {
    if (g[s][u] == 0 && has[s][u]) {
      g[s][u] = -1;
      if (output(u, t)) return true;
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  memset(g, 0x3f, sizeof(g));
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    g[u][v] = g[v][u] = w;
  }
  sssp(n - 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dis[j] + g[i][j] == dis[i]) {
        //printf("%d %d\n", i, j);
        g[i][j] = 1;
        has[i][j] = 1;
      } else g[i][j] = 0;
    }
  }
  int flow = dinic(0, n - 1);
  if (flow < 2) puts("No solution");
  else {
    output(0, n - 1);
    output(0, n - 1);
  }
  return 0;
}

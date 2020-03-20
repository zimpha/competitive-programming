#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100 + 10, M = 300 + 10;

int u[M], v[M];

struct DSU {
  std::vector<int> parent;
  int cnt;

  void init(int n) {
    parent.resize(n);
    for (int i = 0; i < n; ++i) parent[i] = i;
    cnt = n;
  }
  void merge(int u, int v) {
    u = root(u), v = root(v);
    if (u != v) --cnt, parent[u] = v;
  }
  int root(int x) {
    if (x != parent[x]) parent[x] = root(parent[x]);
    return parent[x];
  }
} dsu;

struct MatroidIntersection {
  bool removed[M], graph[M][M];
  int dist[M], from[M];
  bool aug(int n, int m) {
    memset(graph, 0, sizeof(graph));
    std::vector<int> st, ed;
    // graphical matroid: I - x + y \in I_1
    dsu.init(n);
    for (int i = 0; i < m; ++i) {
      if (removed[i]) dsu.merge(u[i], v[i]);
    }
    for (int i = 0; i < m; ++i) {
      if (dsu.root(u[i]) != dsu.root(v[i])) st.push_back(i);
    }
    for (int x = 0; x < m; ++x) if (removed[x]) {
      dsu.init(n);
      for (int i = 0; i < m; ++i) if (removed[i] && i != x) {
        dsu.merge(u[i], v[i]);
      }
      for (int y = 0; y < m; ++y) if (!removed[y]) {
        if (dsu.root(u[y]) != dsu.root(v[y])) graph[x][y] = 1;
      }
    }
    // dual of graphical matroid: I - x + y \in I_2
    for (int y = 0; y < m; ++y) if (!removed[y]) {
      dsu.init(n);
      for (int i = 0; i < m; ++i) if (!removed[i] && i != y) {
        dsu.merge(u[i], v[i]);
      }
      if (dsu.cnt == 1) ed.push_back(y);
      for (int x = 0; x < m; ++x) if (removed[x]) {
        if (dsu.cnt == 1 || (dsu.cnt == 2 && dsu.root(u[x]) != dsu.root(v[x]))) graph[y][x] = 1;
      }
    }
    std::vector<int> queue(st);
    for (int i = 0; i < m; ++i) dist[i] = from[i] = -1;
    for (auto &x: st) dist[x] = 0;
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (int v = 0; v < m; ++v) if (graph[u][v]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          from[v] = u;
          queue.push_back(v);
        }
      }
    }
    int best = -1;
    for (auto &y: ed) if (dist[y] != -1) {
      if (best == -1 || dist[y] < dist[best]) best = y;
    }
    if (best == -1) return false;
    for (int u = best; u != -1; u = from[u]) {
      removed[u] ^= 1;
    }
    return true;
  }
} matroid;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) scanf("%d%d", &u[i], &v[i]);
    memset(matroid.removed, 0, sizeof(matroid.removed));
    while (matroid.aug(n, m));
    int cnt = 0;
    for (int i = 0; i < m; ++i) cnt += matroid.removed[i];
    printf("Case %d: %s\n", cas, cnt == n - 1 ? "YES" : "NO");
  }
  return 0;
}

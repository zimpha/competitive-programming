#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 210, M = 5e4 + 10;

int U[M], V[M], C[M], D[M];
std::vector<int> succ[N], pred[N];
int dist_1n[M], dist_n1[M];
int n, m;

void dijkstra(int *dist, int* from, int src, int forbid, std::vector<int> *edges) {
  for (int i = 1; i <= n; ++i) dist[i] = from[i] = -1;
  std::vector<bool> mark(n + 1);
  dist[src] = 0;
  for (int it = 0; it < n; ++it) {
    int u = -1;
    for (int i = 1; i <= n; ++i) {
      if (dist[i] != -1 && !mark[i] && (u == -1 || dist[i] < dist[u])) u = i;
    }
    if (u == -1) break;
    mark[u] = true;
    for (auto &e: edges[u]) if (e != forbid) {
      int v = U[e] + V[e] - u, w = C[e] + dist[u];
      if (dist[v] == -1 || dist[v] > w) {
        dist[v] = w;
        from[v] = e;
      }
    }
  }
}

int solve(int src, int tar, int* best) {
  static int dist_s[N], dist_t[N], t_dist[N];
  static int from_s[N], from_t[N], t_from[N];
  dijkstra(dist_s, from_s, src, -1, succ);
  dijkstra(dist_t, from_t, tar, -1, pred);
  for (int i = 0; i < m; ++i) {
    int dv = -1, du = -1, ret = -1;
    if (from_s[V[i]] == i) {
      dijkstra(t_dist, t_from, src, i, succ);
      ret = t_dist[tar];
      dv = t_dist[V[i]];
    } else {
      ret = dist_s[tar];
      dv = dist_s[V[i]];
    }
    if (from_t[U[i]] == i) {
      dijkstra(t_dist, t_from, tar, i, pred);
      du = t_dist[U[i]];
    } else {
      du = dist_t[U[i]];
    }
    if (dv != -1 && du != -1) {
      if (ret == -1 || ret > du + dv + C[i]) ret = du + dv + C[i];
    }
    best[i] = ret;
  }
  return dist_s[tar];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d%d", &U[i], &V[i], &C[i], &D[i]);
    succ[U[i]].push_back(i);
    pred[V[i]].push_back(i);
  }
  int d1 = solve(1, n, dist_1n);
  int dn = solve(n, 1, dist_n1);
  int ret = -1;
  if (d1 != -1 && dn != -1) ret = d1 + dn;
  for (int i = 0; i < m; ++i) {
    if (dist_1n[i] == -1 || dist_n1[i] == -1) continue;
    if (ret == -1 || ret > dist_1n[i] + dist_n1[i] + D[i]) {
      ret = dist_1n[i] + dist_n1[i] + D[i];
    }
  }
  printf("%d\n", ret);
  return 0;
}

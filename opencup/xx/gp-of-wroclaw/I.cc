#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using int64 = long long;

const int N = 1e5 + 10, M = 1e6 + 10;

struct Edge {
  int e, n;
} edge[M * 4];

int A[M], B[M];
int64 C[M];
int edges[N], pred[N], succ[N];
int col[N], belong[N];
bool removed[N];
int sz, cc;

void add_edge(int *head, int u, int e) {
  edge[sz] = (Edge){e, head[u]};
  head[u] = sz++;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    sz = 0;
    for (int i = 0; i < n; ++i) edges[i] = -1;
    for (int i = 0; i < m; ++i) {
      scanf("%d%d%lld", &A[i], &B[i], &C[i]);
      --A[i], --B[i];
      add_edge(edges, A[i], i);
    }

    std::vector<int64> ret(n, 0);
    std::vector<bool> mark(m);
    { // first run
      std::vector<int> from(n, -1);
      std::vector<int64> dist(n, -1);
      std::priority_queue<std::pair<int64, int>> pq;
      dist[0] = 0;
      pq.emplace(0, 0);
      while (!pq.empty()) {
        int u = pq.top().second;
        int64 d = -pq.top().first;
        pq.pop();
        if (dist[u] < d) continue;
        for (int it = edges[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          int64 w = C[e];
          if (dist[v] == -1 || dist[v] > w + d) {
            dist[v] = w + d;
            from[v] = e;
            pq.emplace(-dist[v], v);
          }
        }
      }
      for (int i = 0; i < n; ++i) {
        if (from[i] != -1) mark[from[i]] = true;
        ret[i] = dist[i];
      }
      for (int i = 0; i < m; ++i) {
        C[i] += dist[A[i]] - dist[B[i]];
      }
    }
    sz = 0;
    for (int i = 0; i < n; ++i) {
      edges[i] = -1;
      pred[i] = -1;
      succ[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
      if (mark[i]) {
        add_edge(edges, B[i], i);
        add_edge(edges, A[i], i);
      } else {
        add_edge(succ, A[i], i);
        add_edge(pred, B[i], i);
      }
    }
    std::vector<int64> dist(n, -1);
    std::priority_queue<std::pair<int64, int>> pq;
    dist[0] = 0;
    pq.emplace(0, 0);
    for (int i = 0; i < n; ++i) removed[i] = false;
    for (int i = 0; i < n; ++i) col[i] = belong[i] = 0;
    cc = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      int64 d = -pq.top().first;
      pq.pop();
      if (dist[u] < d) continue;
      for (int it = succ[u]; it != -1; it = edge[it].n) {
        int e = edge[it].e, v = A[e] + B[e] - u;
        int64 w = C[e];
        if (dist[v] == -1 || dist[v] > d + w) {
          dist[v] = d + w;
          pq.emplace(-dist[v], v);
        }
      }
      removed[u] = true;
      col[u] = belong[u] = -1;
      std::vector<int> children, small;
      for (int it = edges[u]; it != -1; it = edge[it].n) {
        int e = edge[it].e, v = A[e] + B[e] - u;
        if (!removed[v]) children.push_back(v);
      }
      if (children.size() < 2) continue;

      int dfs_cnt;
      std::function<void(int, int)> dfs1 = [&](int u, int p) {
        dfs_cnt--; belong[u] = cc;
        if (dfs_cnt == 0) return;
        for (int it = edges[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          if (removed[v] || v == p) continue;
          dfs1(v, u);
          if (!dfs_cnt) return;
        }
      };

      int large = children[0];
      for (size_t i = 1; i < children.size(); ++i) {
        int now = children[i];
        for (int s = 1; ; s <<= 1) {
          dfs_cnt = s; cc++;
          dfs1(large, -1);
          int xrem = dfs_cnt;
          dfs_cnt = s; cc++;
          dfs1(now, -1);
          int yrem = dfs_cnt;
          if (!xrem && !yrem) continue;
          if (xrem > yrem) std::swap(large, now);
          small.push_back(now);
          break;
        }
      }

      std::function<void(int, int)> dfs2 = [&](int u, int p) {
        for (int it = succ[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          int64 w = C[e];
          if (col[u] != col[v] || belong[u] == belong[v]) continue;
          // u -> v with w
          if (dist[v] == -1 || dist[v] > d + w) {
            dist[v] = d + w;
            pq.emplace(-dist[v], v);
          }
        }
        int64 min_w = -1;
        for (int it = pred[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          int64 w = C[e];
          if (col[u] != col[v] || belong[u] == belong[v]) continue;
          if (min_w == -1 || min_w > w) min_w = w;
        }
        // some v -> u with min_w
        if (min_w != -1 && (dist[u] == -1 || dist[u] > d + min_w)) {
          dist[u] = d + min_w;
          pq.emplace(-dist[u], u);
        }
        for (int it = edges[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          if (removed[v] || v == p) continue;
          dfs2(v, u);
        }
      };
      
      for (auto &v: small) dfs2(v, u);

      std::function<void(int, int)> dfs3 = [&](int u, int p) {
        col[u] = cc;
        for (int it = edges[u]; it != -1; it = edge[it].n) {
          int e = edge[it].e, v = A[e] + B[e] - u;
          if (removed[v] || v == p) continue;
          dfs3(v, u);
        }
      };

      for (auto &v: small) cc++, dfs3(v, u);
    }
    for (int i = 1; i < n; ++i) {
      if (dist[i] == -1) ret[i] = -1;
      else ret[i] = dist[i] + ret[i] * 2;
      printf("%lld ", ret[i]);
    }
    puts("");
  }
  return 0;
}

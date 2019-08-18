#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>

#include <tuple>

namespace NetFlow {
  using flow_t = int;
  const int N = 1e3 + 10, M = 1e6 + 10;
  const flow_t inf = 2e9;
  struct edge_t {
    int to, nx;
    flow_t cap, flow;
    edge_t() {}
    edge_t(int to, int nx, flow_t cap):
      to(to), nx(nx), cap(cap), flow(0) {}
  } edges[M];
  int G[N], cur[N], pre[N], gap[N], n, sz;
  flow_t dis[N];
  void init(int _n) {
    n = _n, sz = 0;
    memset(G, -1, sizeof(*G) * n);
  }
  void link(int u, int v, flow_t c) {
    edges[sz] = edge_t(v, G[u], c); G[u] = sz++;
    edges[sz] = edge_t(u, G[v], 0); G[v] = sz++;
  }
  flow_t ISAP(int S, int T) {//S -> T
    flow_t maxflow = 0, aug = inf;
    memcpy(cur, G, sizeof(*G) * n);
    memset(gap, 0, sizeof(*gap) * n);
    memset(dis, 0, sizeof(*dis) * n);
    gap[S] = n, pre[S] = S;
    for (int u = S, flag = 0; dis[S] < n; flag = 0) {
      for (int &it = cur[u]; ~it; it = edges[it].nx) {
        int v = edges[it].to;
        if (edges[it].cap > edges[it].flow && dis[u] == dis[v] + 1) {
          aug = std::min(aug, edges[it].cap - edges[it].flow);
          pre[v] = u, u = v, flag = true;
          if (u == T) {
            for (maxflow += aug; u != S; ) {
              u = pre[u];
              edges[cur[u]].flow += aug;
              edges[cur[u] ^ 1].flow -= aug;
            }
            aug = inf;
          }
          break;
        }
      }
      if (flag) continue;
      int mx = n;
      for (int it = G[u]; ~it; it = edges[it].nx) {
        if (edges[it].cap > edges[it].flow && dis[edges[it].to] < mx) {
          mx = dis[edges[it].to];
          cur[u] = it;
        }
      }
      if (--gap[dis[u]] == 0) break;
      ++gap[dis[u] = mx + 1];
      u = pre[u];
    }
    return maxflow;
  }
  bool bfs(int S, int T) {
    static int Q[N];
    memset(dis, -1, sizeof(*dis) * n);
    dis[S] = 0, Q[0] = S;
    for (int h = 0, t = 1; h < t; ++h) {
      for (int u = Q[h], it = G[u]; ~it; it = edges[it].nx) {
        int v = edges[it].to;
        if (dis[v] == -1 && edges[it].cap > edges[it].flow) {
          dis[v] = dis[u] + 1;
          Q[t++] = v;
        }
      }
    }
    return dis[T] != -1;
  }
  flow_t dfs(int u, int T, flow_t low) {
    if (u == T) return low;
    flow_t ret = 0;
    for (int &it = cur[u]; ~it && ret < low; it = edges[it].nx) {
      int v = edges[it].to;
      if (dis[v] == dis[u] + 1 && edges[it].cap > edges[it].flow) {
        flow_t tmp = dfs(v, T, std::min(low - ret, edges[it].cap - edges[it].flow));
        if (tmp > 0) {
          ret += tmp;
          edges[it].flow += tmp;
          edges[it ^ 1].flow -= tmp;
        }
      }
    }
    if (!ret) dis[u] = -1;
    return ret;
  }
  flow_t dinic(int S, int T) {
    flow_t maxflow = 0, tmp;
    while (bfs(S, T)) {
      memcpy(cur, G, sizeof(*G) * n);
      while (tmp = dfs(S, T, inf)) {
        maxflow += tmp;
      }
    }
    return maxflow;
  }
  std::vector<int> reachable(int S) {
    std::vector<int> queue = {S};
    std::vector<int> mark(n);
    mark[S] = 1;
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (int it = G[u]; ~it; it = edges[it].nx) {
        if (edges[it].flow < edges[it].cap && !mark[edges[it].to]) {
          mark[edges[it].to] = 1;
          queue.push_back(edges[it].to);
        }
      }
    }
    return queue;
  }
}

void solve() {
  int k, n;
  scanf("%d%d", &k, &n);
  NetFlow::init(n + 2);
  int S = n, T = n + 1;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int w, m;
    scanf("%d%d", &w, &m);
    if (w > 0) {
      NetFlow::link(S, i, w);
      sum += w;
    } else if (w < 0) {
      NetFlow::link(i, T, -w);
    }
    for (int j = 0; j < m; ++j) {
      int x, w;
      scanf("%d%d", &x, &w);
      NetFlow::link(i, x - 1, w);
    }
  }
  auto cost = NetFlow::ISAP(S, T);
  auto select = NetFlow::reachable(S);
  std::sort(select.begin(), select.end());
  select.pop_back();
  printf("%d\n", (int)select.size());
  for (auto &x: select) {
    printf("%d ", x + 1);
  }
  puts("");
}

int main() {
  solve();
  return 0;
}

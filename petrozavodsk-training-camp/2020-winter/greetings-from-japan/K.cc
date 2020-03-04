#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using flow_t = int;
const flow_t inf = 1e9;

namespace net {
  const int N = 1e4 + 10, M = 1e5 + 10;
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
}

const int N = 100;

char s[N][N];

int main() {
  int n, m, a, b, c;
  scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  
  // 0: (x, y) black horizontal
  // 1: (x, y) black not vertical
  // 2: (x, y) white not horizontal
  // 3: (x, y) white vertical
  auto e = [&](int o, int x, int y) {
    return o * n * m + x * m + y;
  };

  int S = n * m * 4, T = S + 1;
  net::init(T + 1);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    net::link(S, e(1, i, j), a); net::link(e(0, i, j), T, a);
    net::link(S, e(2, i, j), a); net::link(e(3, i, j), T, a);
    if (j + 1 < m) net::link(e(0, i, j), e(0, i, j + 1), b);
    else net::link(e(0, i, j), T, b);
    if (i + 1 < n) net::link(e(1, i + 1, j), e(1, i, j), b);
    else net::link(S, e(1, i, j), b);
    if (j + 1 < m) net::link(e(2, i, j + 1), e(2, i, j), b);
    else net::link(S, e(2, i, j), b);
    if (i + 1 < n) net::link(e(3, i, j), e(3, i + 1, j), b);
    else net::link(e(3, i, j), T, b);
    if (s[i][j] == '#') {
      net::link(e(1, i, j), e(0, i, j), c);
      net::link(S, e(2, i, j), inf);
      net::link(e(3, i, j), T, inf);
    } else {
      net::link(e(0, i, j), e(1, i, j), inf);
      net::link(e(0, i, j), e(3, i, j), c);
      net::link(e(2, i, j), e(1, i, j), c);
    }
  }
  printf("%d\n", net::ISAP(S, T));
  return 0;
}

#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

namespace NetFlow {
  using flow_t = int;
  const int N = 200 + 10, M = 1e5 + 10;
  const flow_t inf = 1e9;
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
}

namespace net = NetFlow;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  net::init(n + 2);
  int S = n, T = n + 1;
  std::vector<int> lower(m), upper(m);
  std::vector<int> balance(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d%d%d", &u, &v, &lower[i], &upper[i]);
    --u, --v;
    net::link(u, v, upper[i] - lower[i]);
    balance[v] += lower[i];
    balance[u] -= lower[i];
  }
  int total = 0;
  for (int i = 0; i < n; ++i) {
    if (balance[i] > 0) {
      net::link(S, i, +balance[i]);
      total += balance[i];
    }
    if (balance[i] < 0) net::link(i, T, -balance[i]);
  }
  total -= net::ISAP(S, T);
  if (total == 0) {
    puts("YES");
    for (int i = 0; i < m; ++i) {
      printf("%d\n", lower[i] + net::edges[i << 1].flow);
    }
  } else {
    puts("NO");
  }
  return 0;
}

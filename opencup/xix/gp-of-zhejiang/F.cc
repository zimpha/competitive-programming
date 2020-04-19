#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

template<typename flow_t, typename cost_t>
struct MCMF {
  static const int N = 4000 + 10, M = 2e4 + 10, inf = 1e9;
  struct node {
    int to, nxt;
    flow_t cap, flow;
    cost_t cost;
    node() {}
    node(int to, int nxt, flow_t cap, cost_t cost):
      to(to), nxt(nxt), cap(cap), flow(0), cost(cost) {}
  } edges[M];
  cost_t phi[N];
  int G[N], cur[N];
  int n, m;
  cost_t min_cost, len;
  flow_t max_flow;
  bool done[N];
  void init(int n) {
    this->n = n;
    this->m = 0;
    std::fill(G, G + n, -1);
  }
  void link(int u, int v, flow_t f, cost_t c) {
    edges[m] = node(v, G[u], f, +c); G[u] = m++;
    edges[m] = node(u, G[v], 0, -c); G[v] = m++;
  }
  // assign weight the cost
  void spfa(int S) {
    for (int i = 0; i < n; ++i) phi[i] = inf;
    std::fill(done, done + n, 0);
    std::queue<int> queue;
    queue.push(S); phi[S] = 0;
    while (!queue.empty()) {
      int u = queue.front(); queue.pop();
      done[u] = false;
      for (int it = G[u]; ~it; it = edges[it].nxt) if (edges[it].cap > edges[it].flow) {
        int v = edges[it].to;
        if (phi[v] > phi[u] + edges[it].cost) {
          phi[v] = phi[u] + edges[it].cost;
          if (!done[v]) queue.push(v);
          done[v] = true;
        }
      }
    }
  }
  flow_t aug(int u, int t, flow_t m){
    if (u == t) return m;
    flow_t su = 0, f;
    done[u] = true;
    for(int i=cur[u];~i;cur[u]=i=edges[i].nxt)
      if (edges[i].cap > edges[i].flow && !done[edges[i].to] && phi[u] + edges[i].cost == phi[edges[i].to]) {
        f = aug(edges[i].to, t, std::min(m, edges[i].cap - edges[i].flow));
        edges[i].flow += f; edges[i ^ 1].flow -= f;
        m -= f; su += f;
        if(!m)break;
      }
    if (su) done[u] = 0;
    return su;
  }
  cost_t dis[N];
  void dijkstra(int s) {
    std::priority_queue<std::pair<cost_t, int>> pq;
    for (int i = 0; i < n; ++i) dis[i] = inf;
    dis[s] = 0; pq.emplace(0, s);
    while (!pq.empty()) {
      auto d = -pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (dis[u] != d) continue;
      for (int it = G[u]; ~it; it = edges[it].nxt) {
        int v = edges[it].to;
        cost_t w = d + edges[it].cost + phi[u] - phi[v];
        if (edges[it].cap > edges[it].flow && w < dis[v]) {
          assert(w >= 0);
          dis[v] = w;
          pq.emplace(-dis[v], v);
        }
      }
    }
    for (int i = 0; i < n; ++i) phi[i] += dis[i];
  }
  std::pair<flow_t, cost_t> run(int S, int T) {
    for (int i = 0; i < n; ++i) phi[i] = 0;
    spfa(S);
    flow_t max_flow = 0;
    cost_t min_cost = 0;
    while (true) {
      dijkstra(S);
      for (int i = 0; i < n; ++i) done[i] = false;
      for (int i = 0; i < n; ++i) cur[i] = G[i];
      auto flow = aug(S, T, inf);
      if (!flow) break;
      max_flow += flow;
      min_cost += phi[T] * flow;
    }
    return {max_flow, min_cost};
  }
};

MCMF<int, int64> flow;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  flow.init(n * 2 + 2);
  std::vector<int> cnt(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    cnt[u] += w; cnt[v] += w;
    flow.link(u, v + n, w, 0);
  }
  int s = n * 2, t = n * 2 + 1;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += cnt[i];
    flow.link(i, i + n, cnt[i], 1);
    flow.link(s, i, cnt[i], 0);
    flow.link(i + n, t, cnt[i], 0);
  }
  ret -= flow.run(s, t).second;
  printf("%d\n", ret);
  return 0;
}

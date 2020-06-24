#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

const int N = 40000 + 10, M = N * 10;
const int inf = 1e9;

template<typename flow_t, typename cost_t>
struct MCMF {
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
  cost_t run(int S, int T, flow_t flow) {
    for (int i = 0; i < n; ++i) phi[i] = 0;
    spfa(S);
    cost_t min_cost = 0;
    while (flow) {
      dijkstra(S);
      for (int i = 0; i < n; ++i) done[i] = false;
      for (int i = 0; i < n; ++i) cur[i] = G[i];
      auto t_flow = aug(S, T, flow);
      if (!t_flow) break;
      flow -= t_flow;
      min_cost += phi[T] * t_flow;
    }
    return min_cost;
  }
};

MCMF<int, int64> flow;

int main() {
  int m, n, k;
  scanf("%d%d%d", &m, &n, &k);
  std::vector<int> w(n);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  flow.init(k);
  for (int i = 1; i < k; ++i) {
    flow.link(i - 1, i, m, 0);
  }
  std::vector<int> last(n, -1);
  int sum = 0;
  for (int i = 0, x; i < k; ++i) {
    scanf("%d", &x); --x;
    sum += w[x];
    if (last[x] != -1) {
      if (last[x] + 1 == i) sum -= w[x];
      else flow.link(last[x] + 1, i, 1, -w[x]);
    }
    last[x] = i;
  }
  auto ret = flow.run(0, k - 1, m - 1);
  printf("%lld\n", sum + ret);
  return 0;
}

#include <bits/stdc++.h>

using ll = long long;

const ll inf = 1e12;

template<typename flow_t, typename cost_t>
struct MCMF {
  static const int N = 500, M = 100000;
  struct node {
    int from, to, nxt;
    flow_t cap, flow;
    cost_t cost;
    node() {}
    node(int from, int to, int nxt, flow_t cap, cost_t cost):
      from(from), to(to), nxt(nxt), cap(cap), flow(0), cost(cost) {}
  } E[M];
  cost_t dis[N];
  int G[N], pre[N], vis[N], n, m;
  void init(int n) {
    this->n = n;
    this->m = 0;
    std::fill(G, G + n, -1);
  }
  void link(int u, int v, flow_t f, cost_t c) {
    E[m] = node(u, v, G[u], f, +c); G[u] = m++;
    E[m] = node(v, u, G[v], 0, -c); G[v] = m++;
  }
  bool extand(int S, int T) {
    std::fill(vis, vis + n, 0);
    std::fill(dis, dis + n, inf);
    std::queue<int> queue;
    dis[S] = 0;
    queue.push(S);
    for (; !queue.empty(); queue.pop()) {
      int u = queue.front();
      vis[u] = false;
      for (int it = G[u]; ~it; it = E[it].nxt) {
        int v = E[it].to;
        if (E[it].cap > E[it].flow && dis[v] > dis[u] + E[it].cost) {
          dis[v] = dis[u] + E[it].cost;
          pre[v] = it;
          if (!vis[v]) queue.push(v);
          vis[v] = true;
        }
      }
    }
    return dis[T] <= 0;// inf; // 改成dis[T] <= 0 求可行流
  }
  std::pair<flow_t, cost_t> run(int S, int T) {
    flow_t max_flow = 0;
    cost_t min_cost = 0;
    while (extand(S, T)) {
      flow_t delta = inf;
      for (int u = T; u != S; u = E[pre[u]].from) {
        delta = std::min(delta, E[pre[u]].cap - E[pre[u]].flow);
      }
      min_cost += delta * dis[T];
      max_flow += delta;
      for (int u = T; u != S; u = E[pre[u]].from) {
        E[pre[u]].flow += delta;
        E[pre[u] ^ 1].flow -= delta;
      }
    }
    return {max_flow, min_cost};
  }
};

MCMF<ll, ll> flow;

int main() {
  int n, tf, ts;
  double dcn, dcf, dcs;
  scanf("%d%lf%lf%lf%d%d", &n, &dcn, &dcf, &dcs, &tf, &ts);
  int cn = int(dcn * 100 + 0.5);
  int cf = int(dcf * 100 + 0.5);
  int cs = int(dcs * 100 + 0.5);
  std::vector<int> R(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &R[i]);
  }
  int S = n * 2, T = n * 2 + 1;
  flow.init(n * 2 + 2);
  int sum = std::accumulate(R.begin(), R.end(), 0);
  for (int i = 0; i < n; ++i) {
    flow.link(i * 2, i * 2 + 1, R[i], -inf);
    flow.link(i * 2 + 1, T, inf, 0);
    flow.link(S, i * 2, inf, cn);
  }
  for (int i = 0; i < n - 1; ++i) {
    flow.link(i * 2, i * 2 + 2, inf, 0);
  }
  for (int i = 0; i + tf < n; ++i) {
    flow.link(i * 2 + 1, (i + tf) * 2, inf, cf);
  }
  for (int i = 0; i + ts < n; ++i) {
    flow.link(i * 2 + 1, (i + ts) * 2, inf, cs);
  }
  ll ret = flow.run(S, T).second - sum * -inf;
  printf("%lld.%02lld\n", ret / 100, ret % 100);
  return 0;
}

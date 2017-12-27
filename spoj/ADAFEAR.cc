#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>

template<typename flow_t, typename cost_t>
struct MCMF {
  static const int N = 4000, M = 300000;
  const flow_t inf = 1e9;
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
    return dis[T] <= 0;
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

MCMF<int, int> flow;

const int N = 2000 + 10;

std::vector<int> fac[N];
int mapping[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int m = n, sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
    int x = a[i];
    for (int p = 2; p * p <= x; ++p) if (x % p == 0) {
      if (!mapping[p]) mapping[p] = m++;
      while (x % p == 0) x /= p;
      fac[i].emplace_back(p);
    }
    if (x > 1) {
      if (!mapping[x]) mapping[x] = m++;
      fac[i].emplace_back(x);
    }
  }
  int S = m++, T = m++;
  flow.init(m);
  for (int i = n; i < S; ++i) {
    flow.link(S, i, 1, 0);
  }
  for (int i = 0; i < n; ++i) {
    flow.link(i, T, 1, 0);
    for (auto &&p: fac[i]) {
      flow.link(mapping[p], i, 1, a[i] / p - a[i]);
    }
  }
  printf("%d\n", sum + flow.run(S, T).second);
  return 0;
}

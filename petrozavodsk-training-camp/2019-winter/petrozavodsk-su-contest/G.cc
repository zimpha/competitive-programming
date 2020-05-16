#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

const int inf = 1e9;

template<typename flow_t, typename cost_t>
struct MCMF {
  static const int N = 200, M = 10000;
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
  int link(int u, int v, flow_t f, cost_t c) {
    E[m] = node(u, v, G[u], f, +c); G[u] = m++;
    E[m] = node(v, u, G[v], 0, -c); G[v] = m++;
    return m - 2;
  }
  void clear() {
    for (int i = 0; i < m; ++i) E[i].flow = 0;
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
    return dis[T] < inf; // 改成dis[T] <= 0 求可行流
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

const int N = 100000 + 10;

MCMF<int, int> mcmf;
int eid[52][3], go[52][3];
char s[N];

int idx(char c) {
  if ('a' <= c && c <= 'z') return (c - 'a') * 2 + 1;
  else return (c - 'A') * 2;
}

int main() {
  int n, k;
  scanf("%d%d%s", &n, &k, s);

  if (k < 0 || k > 2 * n) {
    puts("-1");
    return 0;
  }

  std::vector<int> cnt(52), hole(52);
  for (auto &c: "AabDdeOoPpQqR") hole[idx(c)] = 1;
  hole[idx('B')] = hole[idx('g')] = 2;
  for (int i = 0; i < n; ++i) cnt[idx(s[i])]++;
  memset(eid, -1, sizeof(eid));
  mcmf.init(57);
  int S = 52, T = 53;
  int v[3] = {54, 55, 56};
  for (int i = 0; i < 52; ++i) if (cnt[i]) {
    mcmf.link(S, i, cnt[i], 0);
    std::pair<int, int> cost[3] = {{-1, -1}, {-1, -1}, {-1, -1}};
    for (int j = 0; j < 52; ++j) {
      int w = i <= j ? j - i : 52 + j - i;
      if (cost[hole[j]].first == -1 || cost[hole[j]].first > w) cost[hole[j]] = {w, j};
    }
    for (int j = 0; j < 3; ++j) {
      go[i][j] = (cost[j].second % 2 == 0 ? 'A' : 'a') + cost[j].second / 2;
      eid[i][j] = mcmf.link(i, v[j], cnt[i], cost[j].first);
    }
  }
  int e0 = mcmf.link(v[0], T, 0, 0);
  int e1 = mcmf.link(v[1], T, 0, 0);
  int e2 = mcmf.link(v[2], T, 0, 0);

  auto cost = [&](int c2) {
    int c1 = k - c2 * 2;
    int c0 = n - c1 - c2;
    if (c0 < 0) return inf;
    mcmf.E[e0].cap = c0;
    mcmf.E[e1].cap = c1;
    mcmf.E[e2].cap = c2;
    mcmf.clear();
    auto ret = mcmf.run(S, T);
    if (ret.first == c0 + c1 + c2) return ret.second;
    else return inf;
  };

  int left = 0, right = k / 2;
  while (right - left > 2) {
    int m1 = left + (right - left) / 3;
    int m2 = right - (right - left) / 3;
    if (cost(m1) < cost(m2)) right = m2;
    else left = m1;
  }
  int best = inf, best_cap = -1;
  for (int i = left; i <= right; ++i) {
    int t_best = cost(i);
    if (best_cap == -1 || t_best < best) {
      best = t_best;
      best_cap = i;
    }
  }
  printf("%d\n", best);
  cost(best_cap);
  for (int i = 0; i < n; ++i) {
    int u = idx(s[i]);
    for (int j = 0; j < 3; ++j) {
      if (mcmf.E[eid[u][j]].flow == 0) continue;
      //printf("i=%d j=%d u=%d flow=%d go=%c\n", i, j, u, mcmf.E[eid[u][j]].flow, go[u][j]);
      mcmf.E[eid[u][j]].flow--;
      s[i] = go[u][j];
      break;
    }
  }
  puts(s);
  return 0;
}

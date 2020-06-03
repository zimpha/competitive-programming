#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

const std::vector<std::vector<int>> use = {
  {0, 1, 2, 4, 5, 6},
  {2, 5},
  {0, 2, 3, 4, 6},
  {0, 2, 3, 5, 6},
  {1, 2, 3, 5},
  {0, 1, 3, 5, 6},
  {0, 1, 3, 4, 5, 6},
  {0, 2, 5},
  {0, 1, 2, 3, 4, 5, 6},
  {0, 1, 2, 3, 5, 6}
};

const int N = 1e5 + 10;

char s[N];

template<typename flow_t = int, typename cost_t = int>
struct MCMF_ZKW {
  static const int N = 200, M = 3000, inf = 1e9;
  struct node {
    int to, nxt;
    flow_t cap, flow;
    cost_t cost;
    node() {}
    node(int to, int nxt, flow_t cap, cost_t cost):
      to(to), nxt(nxt), cap(cap), flow(0), cost(cost) {}
  } E[M];
  int G[N], n, m;
  cost_t min_cost, len;
  flow_t max_flow;
  bool done[N];
  void init(int n) {
    this->n = n;
    this->m = 0;
    std::fill(G, G + n, -1);
  }
  void link(int u, int v, flow_t f, cost_t c) {
    E[m] = node(v, G[u], f, +c); G[u] = m++;
    E[m] = node(u, G[v], 0, -c); G[v] = m++;
  }
  flow_t aug(int now, int T, flow_t max_cap) {
    if (now == T) {
      max_flow += max_cap;
      min_cost += max_cap * len;
      return max_cap;
    }
    done[now] = true;
    flow_t upp = max_cap;
    for (int it = G[now]; ~it && upp; it = E[it].nxt) {
      if (E[it].cap > E[it].flow && !E[it].cost && !done[E[it].to]) {
        flow_t delta = aug(E[it].to, T, std::min(upp, E[it].cap - E[it].flow));
        E[it].flow += delta;
        E[it ^ 1].flow -= delta;
        upp -= delta;
      }
    }
    return max_cap - upp;
  }
  bool label(int S, int T) {//不能用于负费用
    cost_t delta = inf;
    for (int u = 0; u < n; ++u) if (done[u]) {
      for (int it = G[u]; ~it; it = E[it].nxt) {
        if (E[it].cap > E[it].flow && !done[E[it].to]) {
          delta = std::min(delta, E[it].cost);
        }
      }
    }
    if (delta == inf) return false;
    for (int u = 0; u < n; ++u) if (done[u]) {
      for (int it = G[u]; ~it; it = E[it].nxt) {
        E[it].cost -= delta;
        E[it ^ 1].cost += delta;
      }
    }
    len += delta;
    return true;
  }
  cost_t dis[N];
  bool label_primal_dual(int S, int T) {
    for (int i = 0; i < n; ++i) dis[i] = inf;
    std::fill(done, done + n, 0);
    dis[T] = 0;
    std::queue<int> queue;
    queue.push(T);
    for (; !queue.empty(); queue.pop()) {
      int u = queue.front();
      done[u] = false;
      for (int it = G[u]; ~it; it = E[it].nxt) {
        int v = E[it].to;
        cost_t cost = dis[u] - E[it].cost;
        if (E[it ^ 1].cap > E[it ^ 1].flow && cost < dis[v]) {
          dis[v] = cost;
          if (!done[v]) queue.push(v);
          done[v] = true;
        }
      }
    }
    for (int u = 0; u < n; ++u) {
      for (int it = G[u]; ~it; it = E[it].nxt) {
        E[it].cost += dis[E[it].to] - dis[u];
      }
    }
    len += dis[S];
    return dis[S] < inf;
  }
  std::pair<flow_t, cost_t> run_primal_dual(int S, int T) {
    max_flow = min_cost = len = 0;
    while (label_primal_dual(S, T)) {
      do {
        std::fill(done, done + n, 0);
      } while (aug(S, T, inf));
    }
    return {max_flow, min_cost};
  }
  std::pair<flow_t, cost_t> run(int S, int T) {
    max_flow = min_cost = len = 0;
    do {
      do {
        std::fill(done, done + n, 0);
      } while (aug(S, T, inf));
    } while (label_primal_dual(S, T));
    return {max_flow, min_cost};
  }
};

MCMF_ZKW<> flow;

int main() {
  int seg[10] = {0};
  for (int i = 0; i < 10; ++i) {
    seg[i] = 0;
    for (auto &x: use[i]) seg[i] ^= 1 << x;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, len;
    scanf("%d%d%s", &n, &len, s);
    std::vector<int> cnt(10), best(10);
    for (int i = 0; i < len; ++i) cnt[s[i] - '0']++;

    auto check = [&](int m) {
      int S = 20, T = 21;
      flow.init(22);
      for (int i = 0; i < 10; ++i) {
        flow.link(i + 10, T,  cnt[i], 0);
      }
      int sum = 0;
      for (int i = 9; i >= m; --i) {
        flow.link(S, i, best[i], 0);
        sum += best[i];
        for (int j = 0; j < 10; ++j) {
          flow.link(i, j + 10, 1e9, __builtin_popcount(seg[i] ^ seg[j]));
        }
      }
      auto ret = flow.run(S, T);
      return ret.first == sum && ret.second <= n;
    };

    for (int m = 9; m >= 0; --m) {
      int l = 0, r = len;
      while (l < r) {
        int mid = (l + r + 1) >> 1;
        best[m] = mid;
        if (check(m)) l = mid;
        else r = mid - 1;
      }
      best[m] = l;
      len -= best[m];
    }

    for (int i = 9; i >= 0; --i) {
      while (best[i]--) putchar('0' + i);
    }
    puts("");
  }
  return 0;
}

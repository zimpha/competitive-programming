#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using i64 = long long;

const int N = 2e5 + 10;

int from[N], to[N], flow[N], cost[N];
int st[N], ed[N], size[N], top[N];
int pos[N], parent[N], sz;
i64 dist[N];
std::vector<int> edges[N];
std::set<std::pair<i64, int>> terms;
std::set<int> leaves;

void dfs1(int u, int p = -1) {
  size[u] = 1;
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (v == p) continue;
    dist[v] = dist[u] + cost[e];
    parent[v] = e;
    dfs1(v, u);
    size[u] += size[v];
  }
}

void dfs2(int u, int chain, int p = -1) {
  top[u] = chain;
  pos[sz] = u;
  st[u] = sz++;
  int son = -1;
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (v == p) continue;
    if (son == -1 || size[v] > size[son]) son = v;
  }
  if (son != -1) {
    dfs2(son, chain, u);
  }
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (v == p || v == son) continue;
    dfs2(v, v, u);
  }
  ed[u] = sz;
  if (size[u] == 1) {
    leaves.insert(st[u]);
    terms.emplace(dist[u], u);
  }
}

struct Node {
  int mi, pos, tag;
  void apply(int v) {
    mi -= v;
    tag += v;
  }
} T[N << 2];

void update(int o) {
  T[o].mi = T[o << 1].mi;
  T[o].pos = T[o << 1].pos;
  if (T[o << 1 | 1].mi < T[o].mi) {
    T[o].mi = T[o << 1 | 1].mi;
    T[o].pos = T[o << 1 | 1].pos;
  }
}

void build(int o, int l, int r) {
  T[o].tag = 0;
  if (l + 1 == r) {
    T[o].mi = flow[parent[pos[l]]];
    T[o].pos = l;
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  update(o);
}

void push(int o) {
  if (T[o].tag != 0) {
    T[o << 1].apply(T[o].tag);
    T[o << 1 | 1].apply(T[o].tag);
    T[o].tag = 0;
  }
}

void sub(int o, int l, int r, int L, int R, int v) {
  if (L <= l && r <= R) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) sub(o << 1, l, m, L, R, v);
  if (R > m) sub(o << 1 | 1, m, r, L, R, v);
  update(o);
}

std::pair<int, int> query(int o, int l, int r, int L, int R) {
  if (L <= l && r <= R) return {T[o].mi, T[o].pos};
  push(o);
  int m = (l + r) >> 1;
  std::pair<int, int> ret = {1e9, 0};
  if (L < m) ret = std::min(ret, query(o << 1, l, m, L, R));
  if (R > m) ret = std::min(ret, query(o << 1 | 1, m, r, L, R));
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d%d", from + i, to + i, flow + i, cost + i);
    --from[i], --to[i];
    edges[from[i]].push_back(i);
    edges[to[i]].push_back(i);
  }
  flow[0] = 1e9;
  parent[0] = 0;
  dfs1(0);
  dfs2(0, 0);
  build(1, 0, n);
  std::vector<std::pair<i64, int>> poly;
  while (!leaves.empty()) {
    auto ret = *terms.begin();
    int u = ret.second;
    std::pair<int, int> best{1e9, 0};
    while (u != 0) {
      best = std::min(best, query(1, 0, n, st[top[u]], st[u] + 1));
      int pe = parent[top[u]];
      u = from[pe] + to[pe] - top[u];
    }
    u = ret.second;
    while (u != 0) {
      sub(1, 0, n, st[top[u]], st[u] + 1, best.first);
      int pe = parent[top[u]];
      u = from[pe] + to[pe] - top[u];
    }
    poly.emplace_back(ret.first, best.first);
    int l = st[pos[best.second]], r = ed[pos[best.second]];
    for (auto it = leaves.lower_bound(l); it != leaves.end(); ) {
      if (*it >= r) break;
      int v = pos[*it];
      terms.erase({dist[v], v});
      it = leaves.erase(it);
    }
  }
  double left = 0, right = 0;
  for (auto &e: poly) right += e.second;
  for (int it = 0; it < 100; ++it) {
    double mid = (left + right) / 2;
    double total = 0, rest = mid;
    for (auto &e: poly) {
      double w = std::min<double>(e.second, rest);
      total += w * e.first;
      rest -= w;
    }
    if (total > 0) right = mid;
    else left = mid;
  }
  printf("%.20f\n", left);
  return 0;
}

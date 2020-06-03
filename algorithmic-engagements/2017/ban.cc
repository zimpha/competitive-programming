#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int64, int>;

const int N = 1e5 + 10;
const int64 inf = 1ll << 60;

struct DynamicRMQ {
  struct Node {
    pii w1, w2;
    int64 tag;
    void apply(int64 v) {
      w1.first += v;
      if (w2.second) w2.first += v;
      tag += v;
    }
  };

  void build(int n, int64 *w, int *idx) {
    this->n = n;
    if (!n) return;
    u.resize(n * 2);
    build(0, n - 1, w, idx);
  }
  void add(int L, int R, int64 w) {
    add(0, n - 1, L, R, w);
  }
  void add(int x, int64 w) {
    add(0, n - 1, x, w);
  }
  int64 get(int x) {
    return get(0, n - 1, x);
  }
  std::pair<int64, int> best() const { return u[id(0, n - 1)].w1;  }
  std::pair<int64, int> second_best() const { return u[id(0, n - 1)].w2; }
  int size() const { return n; }
 private:
  int id(int l, int r) const {
    return l + r | (l != r ? 1 : 0);
  }
  void update(int l, int r, int m) {
    int o = id(l, r);
    int lo = id(l, m);
    int ro = id(m + 1, r);
    if (u[lo].w1 > u[ro].w1) {
      u[o].w1 = u[lo].w1;
      u[o].w2 = std::max(u[lo].w2, u[ro].w1);
    } else {
      u[o].w1 = u[ro].w1;
      u[o].w2 = std::max(u[ro].w2, u[lo].w1);
    }
  }
  void push(int l, int r, int m) {
    int o = id(l, r);
    int lo = id(l, m);
    int ro = id(m + 1, r);
    if (u[o].tag) {
      u[lo].apply(u[o].tag);
      u[ro].apply(u[o].tag);
      u[o].tag = 0;
    }
  }
  void build(int l, int r, int64 *w, int *idx) {
    int o = id(l, r);
    if (l == r) {
      u[o].w1 = {w[idx[l]], -idx[l] - 1};
      u[o].w2 = {-inf, 0};
      return;
    }
    int m = (l + r) >> 1;
    build(l, m, w, idx);
    build(m + 1, r, w, idx);
    update(l, r, m);
  }
  void add(int l, int r, int L, int R, int64 v) {
    int o = id(l, r);
    if (L <= l && R >= r) {
      u[o].apply(v);
      return;
    }
    int m = (l + r) >> 1;
    push(l, r, m);
    if (L <= m) add(l, m, L, R, v);
    if (R > m) add(m + 1, r, L, R, v);
    update(l, r, m);
  }
  void add(int l, int r, int x, int64 v) {
    int o = id(l, r);
    if (l == r) {
      u[o].apply(v);
      return;
    }
    int m = (l + r) >> 1;
    push(l, r, m);
    if (x <= m) add(l, m, x, v);
    else add(m + 1, r, x, v);
    update(l, r, m);
  }
  int64 get(int l, int r, int x) {
    int o = id(l, r);
    if (l == r) return u[o].w1.first;
    int m = (l + r) >> 1;
    push(l, r, m);
    if (x <= m) return get(l, m, x);
    else return get(m + 1, r, x);
  }
  int n;
  std::vector<Node> u;
} rmq[N];

struct Entry {
  int root;
  int parent;
  int st, ed;
};

std::vector<Entry> entries[N];
std::vector<std::pair<int, int64>> edges[N];
int64 weight[N];
int n, q;

namespace centroid {
  int64 cost[N];
  int size[N], mark[N];
  int st[N], ed[N], pos[N];
  int mins, root, total;
  int dfn;

  void init(int n) {
    memset(mark, 0, sizeof(*mark) * n);
  }

  void get_center(int u, int p = -1) {
    int mx = 1; size[u] = 1;
    for (auto &e: edges[u]) {
      int v = e.first;
      if (v == p || mark[v]) continue;
      get_center(v, u);
      size[u] += size[v];
      mx = std::max(mx, size[v]);
    }
    mx = std::max(mx, total - size[u]);
    if (mx < mins) mins = mx, root = u;
  }

  void dfs(int u, int64 w, int p = -1) {
    cost[u] = weight[u] - w;
    size[u] = 1;
    pos[dfn] = u;
    st[u] = dfn++;
    for (auto &e: edges[u]) if (!mark[e.first]) {
      int v = e.first;
      if (v == p) continue;
      dfs(v, w + e.second, u);
      size[u] += size[v];
    }
    ed[u] = dfn;
    entries[u].push_back((Entry){root, p, st[u], ed[u]});
  }

  void work(int u, int tot) {
    total = tot; mins = tot * 2;
    get_center(u);
    mark[u = root] = true;
    dfn = 0;
    size[u] = 0;
    entries[u].push_back((Entry){root, -1, -1, -1});
    for (auto &e: edges[u]) if (!mark[e.first]) {
      dfs(e.first, e.second, u);
      size[u] += size[e.first];
    }
    rmq[u].build(size[u], cost, pos);
    for (auto &e: edges[u]) if (!mark[e.first]) {
      work(e.first, size[e.first]);
    }
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &weight[i]);
  }
  std::map<int64, int64> ew;
  for (int i = 1; i < n; ++i) {
    int u, v;
    int64 w;
    scanf("%d%d%lld", &u, &v, &w);
    --u, --v;
    if (u > v) std::swap(u, v);
    ew[(int64)u * n + v] = w;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }
  centroid::init(n);
  centroid::work(0, n);
  int st = 0;
  for (int i = 0; i < q; ++i) {
    int op, u, v;
    int64 w;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%lld", &u, &w);
      --u;
      for (auto &e: entries[u]) if (e.root != u) {
        rmq[e.root].add(e.st, w - weight[u]);
      }
      weight[u] = w;
    } else {
      scanf("%d%d%lld", &u, &v, &w);
      --u, --v;
      if (u > v) std::swap(u, v);
      int64 old_w = ew[(int64)u * n + v];
      for (auto &e: entries[u]) if (e.parent == v) {
        rmq[e.root].add(e.st, e.ed - 1, old_w - w);
      }
      for (auto &e: entries[v]) if (e.parent == u) {
        rmq[e.root].add(e.st, e.ed - 1, old_w - w);
      }
      ew[(int64)u * n + v] = w;
    }
    pii best{-inf, 0};
    for (auto &e: entries[st]) if (rmq[e.root].size()) {
      auto dis = st == e.root ? 0 : rmq[e.root].get(e.st) - weight[st];
      auto a = rmq[e.root].best();
      auto b = rmq[e.root].second_best();
      if (-a.second - 1 != st) best = std::max(best, {a.first + dis, a.second});
      else best = std::max(best, {b.first + dis, b.second});
      pii c = {weight[e.root] + dis, -e.root - 1};
      if (e.root != st) best = std::max(best, c);
    }
    st = -best.second - 1;
    printf("%d ", st + 1);
  }
  puts("");
  return 0;
}

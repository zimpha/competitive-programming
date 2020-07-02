#include <cstdio>
#include <vector>

const int N = 2e5 + 10;

std::vector<int> edges[N];
int top[N], fa[N], size[N];
int dfn[N], depth[N], hson[N], sz;
int n, q;

struct Node {
  int cnt, lazy, tag;
  void apply_lazy(int v, int l, int r) {
    lazy = v; cnt = v * (r - l);
  }
  void apply_tag(int v) {
    tag = v;
  }
} T[N << 2];

void build(int o, int l, int r) {
  T[o].tag = T[o].lazy = -1;
  T[o].cnt = r - l;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

void push_lazy(int o, int l, int r) {
  int m = (l + r) >> 1;
  if (T[o].lazy != -1) {
    T[o << 1].apply_lazy(T[o].lazy, l, m);
    T[o << 1 | 1].apply_lazy(T[o].lazy, m, r);
    T[o].lazy = -1;
  }
}

void push_tag(int o) {
  if (T[o].tag != -1) {
    T[o << 1].apply_tag(T[o].tag);
    T[o << 1 | 1].apply_tag(T[o].tag);
    T[o].tag = -1;
  }
}

void modify_cnt(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply_lazy(v, l, r);
    return;
  }
  push_lazy(o, l, r);
  int m = (l + r) >> 1;
  if (L < m) modify_cnt(o << 1, l, m, L, R, v);
  if (R > m) modify_cnt(o << 1 | 1, m, r, L, R, v);
  T[o].cnt = T[o << 1].cnt + T[o << 1 | 1].cnt;
}

int query_cnt(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].cnt;
  push_lazy(o, l, r);
  int m = (l + r) >> 1, ret = 0;
  if (L < m) ret += query_cnt(o << 1, l, m, L, R);
  if (R > m) ret += query_cnt(o << 1 | 1, m, r, L, R);
  return ret;
}

void modify_tag(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply_tag(v);
    return;
  }
  push_tag(o);
  int m = (l + r) >> 1;
  if (L < m) modify_tag(o << 1, l, m, L, R, v);
  if (R > m) modify_tag(o << 1 | 1, m, r, L, R, v);
}

int query_tag(int o, int l, int r, int x) {
  if (l + 1 == r) return T[o].tag;
  push_tag(o);
  int m = (l + r) >> 1;
  if (x < m) return query_tag(o << 1, l, m, x);
  else return query_tag(o << 1 | 1, m, r, x);
}

void dfs1(int u, int p = -1) {
  size[u] = 1; fa[u] = p;
  for (auto &v: edges[u]) if (v != p) {
    depth[v] = depth[u] + 1;
    dfs1(v, u);
    size[u] += size[v];
  }
}

bool is_light(int u) {
  return top[fa[u]] != top[u];
}

void dfs2(int u, int chain, int p = -1) {
  dfn[u] = sz++;
  top[u] = chain;
  int hv = -1;
  for (auto &v: edges[u]) if (v != p) {
    if (hv == -1 || size[v] > size[hv]) hv = v;
  }
  hson[u] = hv;
  if (hv != -1) {
    dfs2(hv, chain, u);
  }
  for (auto &v: edges[u]) if (v != p && v != hv) {
    dfs2(v, v, u);
  }
}

void toggle(int u, int v, int ts) {
  for (int tu = top[u], tv = top[v]; tu != tv; ) {
    if (depth[tu] < depth[tv]) std::swap(tu, tv), std::swap(u, v);
    if (hson[u] != -1) modify_cnt(1, 0, n, dfn[hson[u]], dfn[hson[u]] + 1, 1);
    if (u != tu) modify_cnt(1, 0, n, dfn[tu] + 1, dfn[u] + 1, 0);
    modify_tag(1, 0, n, dfn[tu], dfn[u] + 1, ts);
    u = fa[tu]; tu = top[u];
  }
  if (depth[u] < depth[v]) std::swap(u, v);
  if (hson[u]) modify_cnt(1, 0, n, dfn[hson[u]], dfn[hson[u]] + 1, 1);
  if (u != v) modify_cnt(1, 0, n, dfn[v] + 1, dfn[u] + 1, 0);
  modify_tag(1, 0, n, dfn[v], dfn[u] + 1, ts);
  if (fa[v] != -1 && hson[fa[v]] == v) modify_cnt(1, 0, n, dfn[v], dfn[v] + 1, 1);
}

int count(int u, int v, int ts) {
  int ret = 0;
  for (int tu = top[u], tv = top[v]; tu != tv; ) {
    if (depth[tu] < depth[tv]) std::swap(tu, tv), std::swap(u, v);
    if (u != tu) ret += query_cnt(1, 0, n, dfn[tu] + 1, dfn[u] + 1);
    int t_fa = query_tag(1, 0, n, dfn[fa[tu]]);
    int t_tu = query_tag(1, 0, n, dfn[tu]);
    ret += t_tu == -1 || (t_fa != t_tu);
    u = fa[tu]; tu = top[u];
  }
  if (depth[u] < depth[v]) std::swap(u, v);
  if (u != v) ret += query_cnt(1, 0, n, dfn[v] + 1, dfn[u] + 1);
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs1(0);
  dfs2(0, 0);
  build(1, 0, n);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, a, b;
    scanf("%d%d%d", &op, &a, &b);
    --a, --b;
    if (op == 1) toggle(a, b, i);
    else printf("%d\n", count(a, b, i));
  }
  return 0;
}

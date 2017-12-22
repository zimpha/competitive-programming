#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 10, inf = 1e9;

struct Edge {
  int v, nxt;
  Edge() {}
  Edge(int a, int b) : v(a), nxt(b) {}
} E[MAXN << 1];

int sum[MAXN << 2];
int G[MAXN], top[MAXN], pos[MAXN], val[MAXN];
int size[MAXN], dep[MAXN], fa[MAXN];
int n, q, sz;

void dfs1(int u, int f, int d) {
  dep[u] = d; fa[u] = f; size[u] = 1;
  for (int now = G[u]; ~now; now = E[now].nxt) {
    int v = E[now].v; if (v == f) continue;
    dfs1(v, u, d + 1); size[u] += size[v];
  }
}

void dfs2(int u, int chain) {
  int son = -1; pos[u] = sz ++; top[u] = chain;
  for (int now = G[u]; ~now; now = E[now].nxt) {
    int v = E[now].v; if (dep[v] < dep[u]) continue;
    if (son == -1 || size[v] > size[son]) son = v;
  }
  if (son == -1) return; dfs2(son, chain);
  for (int now = G[u]; ~now; now = E[now].nxt) {
    int v = E[now].v; if (v == son || dep[v] < dep[u]) continue;
    dfs2(v, v);
  }
}

int u[MAXN];
void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) u[x] += v;
}
int get(int x) {
  int r(0);
  for (; x >= 0; x -= ~x & x + 1) r += u[x];
  return r;
}
void add(int l, int r, int v) {
  add(l, v); add(r + 1, -v);
}

void query_add(int u, int v) {
  int fu = top[u], fv = top[v], ret = 0;
  while (fu != fv) {
    if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv);
    add(pos[fu], pos[u], 1);
    u = fa[fu]; fu = top[u];
  }
  if (dep[u] > dep[v]) swap(u, v);
  add(pos[u], pos[v], 1);
}

int main() {
  scanf("%d%d", &n, &q); sz = 0;
  for (int i = 1; i <= n; ++ i) G[i] = dep[i] = -1;
  for (int i = 1; i < n; ++ i) {
    int u, v; scanf("%d%d", &u, &v);
    E[sz] = Edge(v, G[u]); G[u] = sz ++;
    E[sz] = Edge(u, G[v]); G[v] = sz ++;
  }
  sz = 0; dfs1(1, -1, 0); dfs2(1, 1);
  for (; q; -- q) {
    int op; scanf("%d", &op);
    if (op == 1) {
      int a, b; scanf("%d%d", &a, &b);
      query_add(a, b);
    } else {
      int x; scanf("%d", &x);
      printf("%d\n", get(pos[x]));
    }
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 50000 + 10;

std::vector<int> edges[N];
int dfn[N], pos[N];
int size[N], top[N], dep[N], parent[N];
int n, sz;

void dfs1(int u, int p = -1) {
  size[u] = 1;
  for (size_t i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    parent[v] = u;
    dfs1(v, u);
    size[u] += size[v];
  }
}

void dfs2(int u, int chain, int p = -1) {
  top[u] = chain;
  pos[sz] = u;
  dfn[u] = sz++;
  int son = -1;
  for (size_t i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    if (v == p) continue;
    if (son == -1 || size[v] > size[son]) son = v;
  }
  if (son != -1) {
    dfs2(son, chain, u);
  }
  for (size_t i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    if (v == p || v == son) continue;
    dfs2(v, v, u);
  }
}

int64 bit[N];

void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) bit[x] += v;
}

int64 get(int x, int64 r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    sz = 0;
    dfs1(0);
    dfs2(0, 0);
    for (int i = 0; i <= n; ++i) bit[i] = 0;
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
      int u, v, k;
      scanf("%d%d%d", &u, &v, &k);
      if (k >= 0) {
        int fu = top[u], fv = top[v];
        while (fu != fv) {
          if (dep[fu] < dep[fv]) std::swap(fu, fv), std::swap(u, v);
          add(dfn[fu], k);
          add(dfn[u] + 1, -k);
          u = parent[fu];
          fu = top[u];
        }
        if (dep[u] > dep[v]) std::swap(u, v);
        add(dfn[u], k);
        add(dfn[v] + 1, -k);
      } else {
        printf("%lld %lld\n", get(dfn[u]), get(dfn[v]));
      }
    }
  }
  return 0;
}

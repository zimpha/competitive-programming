#include <cstdio>
#include <cstring>
#include <vector>
#include <tuple>
#include <algorithm>

using int64 = long long;
const int N = 1e5 + 10, M = 3e5 + 10;
const int LOG = 17;

int X[M], Y[M], C[M], idx[M];
std::vector<int> edges[N], tree[N];
int fa[N][LOG + 1], mx[N][LOG + 1];
int st[N], ed[N], dep[N], sz;
int dsu[N], mark[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void dfs(int u, int p = -1) {
  st[u] = sz++;
  for (auto &e: tree[u]) {
    int v = X[e] + Y[e] - u;
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    fa[v][0] = u;
    mx[v][0] = C[e];
    for (int i = 1; i <= LOG; ++i) if (fa[v][i - 1] != -1) {
      int vv = fa[v][i - 1];
      fa[v][i] = fa[vv][i - 1];
      mx[v][i] = std::max(mx[v][i - 1], mx[vv][i - 1]);
    }
    dfs(v, u);
  }
  ed[u] = sz++;
}

int up(int x, int d) {
  for (int i = 0; d; ++i, d >>= 1) {
    if (d & 1) x = fa[x][i];
  }
  return x;
}

int up_mx(int x, int d) {
  int r = 0;
  for (int i = 0; d; ++i, d >>= 1) {
    if (d & 1) {
      r = std::max(r, mx[x][i]);
      x = fa[x][i];
    }
  }
  return r;
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  x = up(x, dep[x] - dep[y]);
  for (int i = LOG; i >= 0; --i) {
    if (fa[x][i] == fa[y][i]) continue;
    x = fa[x][i]; y = fa[y][i];
  }
  if (x != y) x = fa[x][0];
  return x;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    idx[i] = i;
    scanf("%d%d%d", &X[i], &Y[i], &C[i]);
    --X[i], --Y[i];
    edges[X[i]].push_back(i);
    edges[Y[i]].push_back(i);
  }
  std::sort(idx, idx + m, [&](int a, int b) {
    return C[a] < C[b];
  });
  for (int i = 0; i < n; ++i) {
    memset(fa[i], -1, sizeof(fa[i]));
    dsu[i] = i;
  }
  int64 sum = 0;
  for (int i = 0; i < m; ++i) {
    int e = idx[i], u = get(X[e]), v = get(Y[e]);
    if (u != v) {
      tree[X[e]].push_back(e);
      tree[Y[e]].push_back(e);
      sum += C[e];
      dsu[u] = v;
    }
  }

  sz = 0;
  dep[0] = 0;
  dfs(0);

  for (int src = 0; src < n; ++src) {
    static int ver[N], stk[N];
    m = 0;
    ver[m++] = src;
    for (auto &e: edges[src]) ver[m++] = X[e] + Y[e] - src;
    for (int i = 0; i < m; ++i) mark[ver[i]] = 1;
    std::sort(ver, ver + m, [&](int x, int y) {
      return st[x] < st[y];
    });
    int mm = m;
    for (int i = 0; i + 1 < m; ++i) {
      int x = lca(ver[i], ver[i + 1]);
      if (!mark[x]) mark[x] = 1, ver[mm++] = x;
    }
    m = mm;
    std::sort(ver, ver + m, [&](int x, int y) {
      return st[x] < st[y];
    });
    for (int i = 0; i < m; ++i) dsu[i] = i, idx[ver[i]] = i;
    int64 ret = sum;
    for (auto &e: edges[src]) {
      dsu[idx[X[e] + Y[e] - src]] = idx[src];
      ret += C[e];
    }

    mm = 0; stk[mm++] = ver[0];
    std::vector<std::tuple<int, int, int>> aux;
    for (int i = 1; i < m; ++i) {
      while (st[ver[i]] < st[stk[mm - 1]] || ed[ver[i]] > ed[stk[mm - 1]]) --mm;
      int u = stk[mm - 1], v = ver[i];
      if (dep[u] < dep[v]) std::swap(u, v);
      int w = up_mx(u, dep[u] - dep[v]);
      ret -= w;
      aux.emplace_back(w, idx[u], idx[v]);
      stk[mm++] = ver[i];
    }
    std::sort(aux.begin(), aux.end());
    for (auto &e: aux) {
      int w = std::get<0>(e), u = std::get<1>(e), v = std::get<2>(e);
      if (get(u) != get(v)) {
        dsu[get(u)] = get(v);
        ret += w;
      }
    }
    for (int i = 0; i < m; ++i) mark[ver[i]] = 0;
    printf("%lld\n", ret);
  }
  return 0;
}

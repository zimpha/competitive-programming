#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using int64 = long long;
const int N = 200000 + 10, K = 18;

std::vector<int> edges[N];
int dep[N], f[N][K + 1];
int st[N], ed[N], loc[N << 1];
int n, m, P, dfn;

void dfs(int x, int par = -1) {
  loc[st[x] = dfn++] = x;
  for (int i = 1; i <= K; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
  for (auto &y: edges[x]) if (y != par) {
    dep[y] = dep[f[y][0] = x] + 1;
    dfs(y, x);
  }
  loc[ed[x] = dfn++] = x;
}

int lca(int x, int y) {
  if (x == y) return x;
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = K; ~i; --i) {
    if (dep[f[x][i]] >= dep[y]) x = f[x][i];
  }
  if (x == y) return x;
  for (int i = K; ~i; --i) {
    if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
  }
  return f[x][0];
}

namespace mo {
  int vis[N], ret;
  void deal(int x) {//这部分维护序列
    if (vis[x]) {
      if (vis[x - 1] && vis[x + 1]) ++ret;
      else if (!vis[x - 1] && !vis[x + 1]) --ret;
    } else {
      if (vis[x - 1] && vis[x + 1]) --ret;
      else if (!vis[x - 1] && !vis[x + 1]) ++ret;
    }
    vis[x] ^= 1;
  }
}

struct Node {
  int l, r, z, id;
  bool operator < (const Node &rhs) {
    return l / P == rhs.l / P ? r < rhs.r : l / P < rhs.l / P;
  }
} Q[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(dep[1] = 1);
  P = sqrt(n * 2);
  std::vector<int> ret(m);
  for (int i = 0; i < m; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    if (st[x] > st[y]) std::swap(x, y);
    int z = lca(x, y);
    Q[i].id = i;
    if (z == x) Q[i].l = st[x], Q[i].r = st[y];
    else Q[i].l = ed[x], Q[i].r = st[y], Q[i].z = z;
  }
  std::sort(Q, Q + m);
  for (int i = 0, l = 0, r = -1; i < m; ++i) {
    while (r < Q[i].r) mo::deal(loc[++r]);
    while (r > Q[i].r) mo::deal(loc[r--]);
    while (l < Q[i].l) mo::deal(loc[l++]);
    while (l > Q[i].l) mo::deal(loc[--l]);
    if (Q[i].z) mo::deal(Q[i].z);
    ret[Q[i].id] = mo::ret;
    if (Q[i].z) mo::deal(Q[i].z);
  }
  for (int i = 0; i < m; ++ i) printf("%d\n", ret[i]);
  return 0;
}

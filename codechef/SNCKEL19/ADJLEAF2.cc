#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

const int N = 500000 + 10, POW = 20;

std::vector<int> G[N];

namespace LCA {
  int fa[N][POW + 1], dep[N];
  int st[N], ed[N], sz = 0;
  void dfs(std::vector<int> G[], int u, int p = -1) {
    st[u] = sz++;
    memset(fa[u], -1, sizeof(fa[u]));
    fa[u][0] = p;
    dep[u] = p == -1 ? 0 : dep[p] + 1;
    for (auto &&v: G[u]) if (v != p) dfs(G, v, u);
    ed[u] = sz++;
  }
  void build(int n) {
    for (int i = 1; (1 << i) <= n; ++i) {
      for (int j = 0; j < n; ++j) if (~fa[j][i - 1]) {
        fa[j][i] = fa[fa[j][i - 1]][i - 1];
      }
    }
  }
  int up(int u, int d) {
    for (int i = 0; d; ++i, d >>= 1) {
      if (d & 1) u = fa[u][i];
    }
    return u;
  }
  int lca(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    u = up(u, dep[u] - dep[v]);
    for (int i = POW; i >= 0; --i) {
      if (fa[u][i] == fa[v][i]) continue;
      u = fa[u][i];
      v = fa[v][i];
    }
    if (u != v) u = fa[u][0];
    return u;
  }
}

using namespace LCA;

int a[N],q[N];
bool vip[N],vis[N];
bool cmp(int x,int y){return st[x]<st[y];}
int pos[N];
std::vector<int> H[N];

void addedge(int u, int v) {
  std::cout << "add " << u << " " << v << std::endl;
  H[u].push_back(v);
  H[v].push_back(u);
}

int size[N], f[N], g[N];

bool gao(int u, int p = -1) {
  size[u] = 0;
  f[u] = 1e9, g[u] = -1;
  int cnt = 0;
  bool ret = true;
  for (auto &&v: H[u]) {
    if (v == p) continue;
    if (!gao(v, u)) return false;
    size[u] += size[v];
    f[u] = std::min(f[u], f[v]);
    g[u] = std::max(g[u], g[v]);
    ++cnt;
  }
  if (cnt == 0) {
    size[u] = 1;
    f[u] = g[u] = pos[u];
  }
  if (!ret) return false;
  if (g[u] - f[u] != size[u] - 1) return false;
  std::cout << f[u] << " " << g[u] << " " << size[u] << std::endl;
  return true;
}

void solve(int m, int r) {
  a[0] = r;
  for (int i = 0; i <= m; ++i) {
    pos[a[i]] = i;
    vis[a[i]] = 1;
  }
  std::sort(a, a + m + 1, cmp);
  int tot = m, x;

  for (int i = 0; i < m; i++) if (!vis[x = lca(a[i], a[i+1])]) vis[a[++tot] = x]=1;
  m = tot;
  std::sort(a, a + m + 1, cmp);
  for (int i = 0; i <= m; ++i) std::cout << a[i] << " ";
  puts("");
  int t, i;
  for(q[t = 1]=a[0], i = 1; i <= m; q[++t] = a[i++]){
    while(st[a[i]] < st[q[t]]||ed[a[i]]>ed[q[t]])t--;
    addedge(q[t],a[i]);
  }
  for (int i = 0; i <= m; ++i) {
    pos[a[i]] = 0;
    vis[a[i]] = 0;
    H[a[i]].clear();
  }
  bool ok = gao(r);
  if (ok) puts("Yes");
  else puts("No");
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  LCA::dfs(G, 0);
  LCA::build(n);
  for (int i = 0; i < q; ++i) {
    int m, r;
    scanf("%d%d", &r, &m);
    --r;
    for (int i = 1; i <= m; ++i) {
      scanf("%d", &a[i]);
      --a[i];
    }
    solve(m, r);
  }
  return 0;
}

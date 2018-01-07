#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int S = 1e6 + 10, N = 2e5 + 10;

int cnt[S], gdp[N];
int dis[N], fa[N][20], dep[N];
std::vector<int> edges[N];
int n, k, q;

void dfs(int u, int p = -1) {
  for (auto &&v: edges[u]) if (v != p) {
    fa[v][0] = u;
    dep[v] = dep[u] + 1;
    dis[v] = dis[u] + (cnt[gdp[v]] >= k);
    dfs(v, u);
  }
}

namespace LCA {
  const static int POW = 17;
  void build(int n) {
    for (int i=1;(1<<i)<=n;++i) {
      for (int j=0;j<n;++j) if (~fa[j][i-1]) {
        fa[j][i]=fa[fa[j][i-1]][i-1];
      }
    }
  }
  int up(int u, int d) {
    for (int i=0;d;++i,d>>=1) if (d&1) u=fa[u][i];
    return u;
  }
  int ask(int u, int v) {
    if (dep[u]<dep[v]) std::swap(u,v);
    u=up(u,dep[u]-dep[v]);
    for (int i=POW;i>=0;--i) {
      if (fa[u][i]==fa[v][i]) continue;
      u=fa[u][i]; v=fa[v][i];
    }
    if (u!=v) u=fa[u][0]; return u;
  }
}

int main() {
  for (int i = 2; i < S; ++i) if (!cnt[i]) {
    for (int j = i; j < S; j += i) cnt[j]++;
  }
  scanf("%d%d%d", &n, &k, &q);
  for (int i = 0; i < n; ++i) {
    memset(fa[i], -1, sizeof(fa[i]));
    scanf("%d", &gdp[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  dep[0] = 0;
  dis[0] = cnt[gdp[0]] >= k;
  dfs(0);
  LCA::build(n);
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    int z = LCA::ask(x, y);
    int ret = dis[x] + dis[y] - 2 * dis[z] + (cnt[gdp[z]] >= k);
    printf("%d\n", ret);
  }
  return 0;
}

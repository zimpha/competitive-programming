#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int N = 3e5 + 10, POW = 20;
const int mod = 998244353;

std::vector<int> edges[N];
int n, k;

namespace LCA {
  int fa[N][POW + 1], dep[N];
  void dfs(std::vector<int> G[], int u, int p = -1) {
    memset(fa[u], -1, sizeof(fa[u]));
    fa[u][0] = p;
    dep[u] = p == -1 ? 0 : dep[p] + 1;
    for (auto &&v: G[u]) if (v != p) dfs(G, v, u);
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
  int ask(int u, int v) {
    if (u == -1) return v;
    if (v == -1) return u;
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

std::vector<int> g[N];
int64 dp[N][2];
int size[N];
int a[N], dsu[N];
int b[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void color(int u, int f, int c) {
  f = get(f); u = get(u);
  while (LCA::dep[u] > LCA::dep[f]) {
    int fu = LCA::fa[u][0];
    if (a[fu] && a[fu] != c) {
      puts("0");
      exit(0);
    }
    dsu[u] = fu;
    a[fu] = c;
    u = get(fu);
  }
}

void color(int u, int v, int f, int c) {
  color(u, f, c);
  color(v, f, c);
}

void solve(int u, int p = -1) {
  size[u] = 1 <= u && u <= k;
  std::vector<int64> x, y;
  int m = 0;
  for (auto &&v: g[u]) if (v != p) {
    solve(v, u);
    size[u] += size[v];
    if (!size[v]) continue;
    ++m;
    x.push_back(dp[v][0]);
    y.push_back(dp[v][1]);
  }
  if (!size[u]) return;
  if (1 <= u && u <= k) {
    dp[u][1] = 1;
    for (int i = 0; i < m; ++i) {
      dp[u][1] = dp[u][1] * (x[i] + y[i]) % mod;
    }
  } else {
    dp[u][0] = 1;
    dp[u][1] = 0;
    for (int i = 0; i < m; ++i) {
      dp[u][0] = dp[u][0] * (y[i] + x[i]) % mod;
    }
    std::vector<int64> sf(y.size() + 1, 1);
    for (int i = y.size() - 1; i >= 0; --i) sf[i] = sf[i + 1] * (y[i] + x[i]) % mod;
    int64 pr = 1;
    for (int i = 0; i < m; ++i) {
      dp[u][1] += y[i] * sf[i + 1] % mod * pr % mod;
      dp[u][1] %= mod;
      pr = pr * (y[i] + x[i]) % mod;
    }
  }
}

int main() {
  k = 2;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) b[i] = a[i];
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  for (int i = 0; i < n; ++i) dsu[i] = i;
  LCA::dfs(edges, 0);
  LCA::build(n);
  std::vector<int> top(k + 1, -1);
  for (int i = 0; i < n; ++i) if (b[i]) {
    if (top[b[i]] == -1) top[b[i]] = i;
    int u = LCA::ask(i, top[b[i]]);
    color(i, top[b[i]], u, b[i]);
    top[b[i]] = u;
  }
  int m = k;
  for (int i = 0; i < n; ++i) {
    if (!a[i]) a[i]=++m;
  }
  for (int u = 0; u < n; ++u) {
    for (auto &&v: edges[u]) {
      if (a[u] != a[v]) {
        g[a[u]].push_back(a[v]);
      }
    }
  }
  solve(1);
  printf("%lld\n", dp[1][1]);
  return 0;
}

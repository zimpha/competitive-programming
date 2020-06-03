#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 1e5 + 10, mod = 1e9 + 7, POW = 16;

struct edge_t {
  int v, w, l;
};

using int64 = long long;

std::vector<edge_t> edges[N];
std::vector<int> parent, order;
int64 odd[N], even[N], mark[N];
int n, dep[N], fa[N][POW + 1];

void dfs(int u) {
  mark[u] = 1;
  for (auto &&e : edges[u]) {
    if (mark[e.v]) continue;
    dep[e.v] = dep[u] + 1;
    fa[e.v][0] = u;
    odd[e.v] = odd[u];
    even[e.v] = even[u];
    if (e.l & 1) odd[e.v] += e.w;
    else even[e.v] += e.w;
    parent[e.v] = u;
    dfs(e.v);
  }
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

int main() {
  scanf("%d", &n);
  parent.resize(n);
  int64 ret = 0;
  for (int i = 1; i < n; ++i) {
    int u, v, w, l;
    scanf("%d%d%d%d", &u, &v, &w, &l);
    --u, --v;
    edges[u].push_back((edge_t){v, w, l});
    edges[v].push_back((edge_t){u, w, l});
    ret += (int64)l * w;
    if (l & 1) ret += w;
    ret %= mod;
  }
  memset(fa, -1, sizeof(fa));
  dfs(0);
  build(n);
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    int f = ask(u, v);
    int64 res = ret - (odd[u] + odd[v] - odd[f] * 2);
    res += even[u] + even[v] - even[f] * 2;
    res %= mod;
    res += mod;
    res %= mod;
    printf("%lld\n", res);
  }
  return 0;
}
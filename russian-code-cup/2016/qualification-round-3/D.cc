#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100000 + 10;

std::vector<int> edges[N];
int fa[N][20], dep[N];
int n, st[N], ed[N], sz;

void dfs(int u) {
  st[u] = sz++;
  for (auto &&v: edges[u]) {
    fa[v][0] = u;
    dep[v] = dep[u] + 1;
    dfs(v);
  }
  ed[u] = sz;
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
  for (int i = 16; i >= 0; --i) {
    if (fa[u][i] == fa[v][i]) continue;
    u = fa[u][i];
    v = fa[v][i];
  }
  if (u != v) u = fa[u][0];
  return u;
}

int bit[N];

void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) bit[x] += v;
}

int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int p;
    scanf("%d", &p);
    edges[p - 1].emplace_back(i);
  }
  memset(fa, -1, sizeof(fa));
  dfs(0);
  for (int b = 1; (1 << b) <= n; ++b) {
    for (int i = 0; i < n; ++i) if (fa[i][b - 1] != -1) {
      fa[i][b] = fa[fa[i][b - 1]][b - 1];
    }
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op;
    scanf("%d", &op);
    if (op == 2) {
      int x;
      scanf("%d", &x);
      add(st[x - 1], -1);
      add(ed[x - 1], +1);
    } else {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      int z = lca(x, y);
      printf("%d\n", dep[x] + get(st[x]) + dep[y] + get(st[y]) - 2 * (dep[z] + get(st[z])));
    }
  }
  return 0;
}

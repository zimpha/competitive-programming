#include <cstdio>
#include <vector>

const int N = 250000 + 10;

std::vector<int> edges1[N], edges2[N];
int fa[20][N], dsu[N], depth[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void dfs1(int u, int p = 0) {
  fa[0][u] = p;
  depth[u] = depth[p] + 1;
  for (int i = 1; i < 18; ++i) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  for (auto &v: edges1[u]) {
    if (v != p) dfs1(v, u);
  }
}

void dfs2(int u, int p = 0) {
  for (auto &v: edges2[u]) if (v != p) {
    dfs2(v, u);
    int x = get(u), y = get(v);
    for (int i = 17; i >= 0; --i) {
      if (depth[get(fa[i][x])] > depth[y]) x = get(fa[i][x]);
    }
    if (get(fa[0][x]) != y) x = y;
    printf("%d %d %d %d\n", x, fa[0][x], u, v);
    dsu[x] = fa[0][x];
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges1[u].push_back(v);
    edges1[v].push_back(u);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges2[u].push_back(v);
    edges2[v].push_back(u);
  }
  dfs1(1);
  for (int i = 1; i <= n; ++i) dsu[i] = i;
  printf("%d\n", n - 1);
  dfs2(1);
  return 0;
}

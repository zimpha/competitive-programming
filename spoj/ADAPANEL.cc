#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

constexpr int N = 2e5 + 10, M = 500;
constexpr int mod = 1e9 + 7;

int f[N], g[N], h[N];

void prepare() {
  f[0] = 1;
  for (int i = 1; i < M; ++i) {
    for (int j = i; j < N; ++j) {
      f[j] += f[j - i];
      if (f[j] >= mod) f[j] -= mod;
    }
  }
  memcpy(g, f, sizeof(f));
  for (int i = 1; i < M; ++i) {
    memset(h, 0, sizeof(h));
    for (int j = i; j < N; ++j) {
      if (j >= M) h[j] += f[j - M];
      if (j >= i) h[j] += h[j - i];
      if (h[j] >= mod) h[j] -= mod;
      g[j] += h[j];
      if (g[j] >= mod) g[j] -= mod;
    }
    memcpy(f, h, sizeof(f));
  }
}

struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], size[N], col[N];
  int stk[N], top, scc_cnt, sz;
  void dfs(int x, const std::vector<int> G[]) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &y: G[x]) {
      if (!dfn[y]) {
        dfs(y, G);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      size[scc_cnt++] = 0;
      do {
        ++size[scc_cnt - 1];
        col[stk[top]] = scc_cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n,const std::vector<int> G[]) {
    sz = top = scc_cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i,G);
    }
  }
} scc;

std::vector<int> edges[N];

int main() {
  prepare();
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    edges[a].push_back(b);
  }
  scc.run(n, edges);
  int ret = 1;
  for (int i = 0; i < scc.scc_cnt; ++i) {
    ret = 1ll * ret * g[scc.size[i]] % mod;
  }
  printf("%d\n", ret);
  return 0;
}

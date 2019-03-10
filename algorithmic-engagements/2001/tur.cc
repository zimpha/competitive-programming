#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

static const int N = 1000 + 10;

struct Tarjan {// index from 0 to n - 1
  std::vector<int> SCC[N];
  int low[N], dfn[N], col[N];
  int stk[N], top, cnt, sz;
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
      SCC[cnt++].clear();
      do {
        SCC[cnt - 1].push_back(stk[top]);
        col[stk[top]] = cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n,const std::vector<int> G[]) {
    sz = top = cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i,G);
    }
  }
} scc;

std::vector<int> edges[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int x;
      scanf("%d", &x);
      edges[x - 1].push_back(i);
    }
  }
  scc.run(n, edges);
  std::vector<int> deg(scc.cnt);
  for (int u = 0; u < n; ++u) {
    for (auto &&v: edges[u]) if (scc.col[u] != scc.col[v]) {
      deg[scc.col[v]]++;
    }
  }
  int cnt = 0, ret = 0, p;
  for (int i = 0; i < scc.cnt; ++i) {
    if (deg[i] == 0) ++cnt, p = i;
  }
  if (cnt != 1) ret = 0;
  else ret = scc.SCC[p].size();
  printf("%d\n", ret);
  return 0;
}

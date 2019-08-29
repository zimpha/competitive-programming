#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

static const int N = 100000 + 10;

struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], col[N];
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
      do {
        col[stk[top]] = scc_cnt;
      } while (stk[top--] != x);
      scc_cnt++;
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
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    edges[a].push_back(b);
  }
  scc.run(n, edges);
  std::vector<int> in(scc.scc_cnt), out(scc.scc_cnt);
  for (int u = 0; u < n; ++u) {
    for (auto &v: edges[u]) {
      if (scc.col[u] != scc.col[v]) in[scc.col[v]]++, out[scc.col[u]]++;
    }
  }
  int ret = 0;
  if (scc.scc_cnt == 1) ret = 0;
  else {
    int a = 0, b = 0;
    for (int i = 0; i < scc.scc_cnt; ++i) {
      a += in[i] == 0;
      b += out[i] == 0;
    }
    ret = std::max(a, b);
  }
  printf("%d\n", ret);
  return 0;
}

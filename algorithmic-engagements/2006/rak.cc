#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <bitset>

static const int N = 20000 + 10;
using state = std::bitset<10000>;

struct Tarjan {// index from 0 to n - 1
  std::vector<int> SCC[N];
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
      SCC[scc_cnt++].clear();
      do {
        SCC[scc_cnt - 1].push_back(stk[top]);
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
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v, s;
    scanf("%d%d%d", &u, &v, &s);
    --u, --v;
    if (s == 0) {
      edges[u].push_back(v);
      edges[v + n].push_back(u + n);
    } else {
      edges[u].push_back(v + n);
      edges[v + n].push_back(u);
    }
  }
  scc.run(n * 2, edges);
  std::vector<int> ret(n), mark(n);
  for (int i = scc.scc_cnt - 1; i >= 0; --i) {
    int cnt = 0;
    for (auto &x: scc.SCC[i]) {
      int y = x < n ? x : x - n;
      if (!mark[y]) ++cnt;
      mark[y] = 1;
    }
    for (auto &x: scc.SCC[i]) {
      int y = x < n ? x : x - n;
      mark[y] = 0;
      if (x >= n) ret[x - n] = cnt;
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ret[i] - 1);
  }
  return 0;
}


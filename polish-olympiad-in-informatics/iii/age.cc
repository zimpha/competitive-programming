#include <cstdio>
#include <vector>
#include <cstring>

static const int N = 100000 + 10;

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
  int n, p, m;
  scanf("%d", &n);
  scanf("%d", &p);
  std::vector<int> cost(n, -1);
  for (int i = 0; i < p; ++i) {
    int x, w;
    scanf("%d%d", &x, &w);
    cost[x - 1] = w;
  }
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
  }
  scc.run(n, edges);
  std::vector<int> deg(scc.scc_cnt);
  std::vector<int> bribe(scc.scc_cnt, -1);
  for (int u = 0; u < n; ++u) {
    if (cost[u] != -1 && (bribe[scc.col[u]] == -1 || bribe[scc.col[u]] > cost[u])) {
      bribe[scc.col[u]] = cost[u];
    }
    for (auto &&v: edges[u]) if (scc.col[u] != scc.col[v]) {
      deg[scc.col[v]]++;
    }
  }
  bool valid = true;
  int ret = 0;
  for (int i = 0; i < scc.scc_cnt; ++i) {
    if (deg[i] == 0 && bribe[i] == -1) valid = false;
    if (deg[i] == 0) ret += bribe[i];
  }
  if (!valid) {
    puts("NIE");
    std::vector<int> queue;
    std::vector<bool> mark(n);
    for (int i = 0; i < n; ++i) if (cost[i] != -1) {
      queue.push_back(i);
      mark[i] = 1;
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue.front();
      for (auto &&v: edges[u]) if (!mark[v]) {
        queue.push_back(v);
        mark[v] = 1;
      }
    }
    for (int i = 0; i < n; ++i) if (!mark[i]) {
      printf("%d\n", i + 1);
      break;
    }
  } else {
    puts("TAK");
    printf("%d\n", ret);
  }
  return 0;
}

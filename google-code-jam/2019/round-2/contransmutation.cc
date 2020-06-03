#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

static const int N = 100000 + 10;
const int mod = 1e9 + 7;

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
std::vector<int> e[N];
bool mark[N];

void dfs(int u) {
  mark[u] = 1;
  for (auto &&v: edges[u]) {
    if (!mark[v]) dfs(v);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      edges[i].clear();
      e[i].clear();
    }
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      edges[i].push_back(x);
      edges[i].push_back(y);
    }
    std::vector<int> G(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &G[i]);
      mark[i] = 0;
    }
    for (int i = 0; i < n; ++i) if (G[i] && !mark[i]) {
      dfs(i);
    }
    for (int u = 0; u < n; ++u) {
      for (auto &&v: edges[u]) if (mark[u] && mark[v]) {
        e[u].push_back(v);
      }
    }
    for (int i = 0; i < n; ++i) edges[i] = e[i];
    scc.run(n, edges);
    std::vector<int> unbound(scc.scc_cnt, 0);
    std::vector<int> cycle(scc.scc_cnt, 0);
    std::vector<int> deg(n, 0);
    for (int u = 0; u < n; ++u) {
      for (auto &&v: edges[u]) if (scc.col[u] == scc.col[v]) {
        deg[v]++;
      }
    }
    for (int i = 0; i < scc.scc_cnt; ++i) {
      for (auto &&u: scc.SCC[i]) {
        if (deg[u] == 0) continue;
        if (deg[u] != 1) unbound[i] = 1;
      }
      cycle[i] = scc.SCC[i].size() != 1 || deg[scc.SCC[i][0]] != 0;
    }
    std::vector<int> dp(scc.scc_cnt, 0);
    std::vector<int> from_cycle(scc.scc_cnt, 0);
    deg.assign(scc.scc_cnt, 0);
    for (int i = 0; i < scc.scc_cnt; ++i) {
      e[i].clear();
    }
    for (int u = 0; u < n; ++u) {
      dp[scc.col[u]] += G[u];
      dp[scc.col[u]] %= mod;
      for (auto &&v: edges[u]) if (scc.col[u] != scc.col[v]) {
        deg[scc.col[v]]++;
        e[scc.col[u]].push_back(scc.col[v]);
      }
    }
    std::vector<int> queue;
    for (int i = 0; i < scc.scc_cnt; ++i) {
      if (deg[i] == 0) queue.push_back(i);
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (auto &&v: e[u]) {
        unbound[v] |= unbound[u];
        from_cycle[v] |= from_cycle[u];
        from_cycle[v] |= cycle[u];
        dp[v] += dp[u];
        dp[v] %= mod;
        --deg[v];
        if (deg[v] == 0) queue.push_back(v);
      }
    }
    if (unbound[scc.col[0]] || from_cycle[scc.col[0]]) printf("Case #%d: UNBOUNDED\n", cas);
    else printf("Case #%d: %d\n", cas, dp[scc.col[0]]);
  }
  return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

static const int N = 100000 + 10;
struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], col[N];
  int stk[N], top, scc_cnt, sz;
  void dfs(int x, const std::vector<std::pair<int, int>> G[]) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &e: G[x]) {
      int y = e.first;
      if (!dfn[y]) {
        dfs(y, G);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      ++scc_cnt;
      do {
        col[stk[top]] = scc_cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n,const std::vector<std::pair<int, int>> G[]) {
    sz = top = scc_cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i,G);
    }
  }
} scc;

std::vector<std::pair<int, int>> edges[N];
int depth[N], mark[N], best;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

void dfs(int u) {
  for (auto &&e: edges[u]) {
    int v = e.first, w = e.second;
    if (scc.col[u] != scc.col[v]) continue;
    if (!mark[v]) {
      depth[v] = depth[u] + w;
      mark[v] = true;
      dfs(v);
    } else {
      best = gcd(best, std::abs(depth[u] - depth[v] + w));
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u - 1].emplace_back(v - 1, w);
  }
  scc.run(n, edges);
  std::vector<int> ret(scc.scc_cnt);
  for (int i = 0; i < n; ++i) if (!mark[i]) {
    best = 0;
    mark[i] = 1;
    dfs(i);
    if (best == 0) best = -1;
    ret[scc.col[i]] = best;
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ret[scc.col[i]]);
  }
  return 0;
}

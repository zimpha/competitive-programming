#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

constexpr int N = 1.5e5 + 10;

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

std::vector<int> edges[N], succ[N], pred[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].emplace_back(v - 1);
  }
  scc.run(n, edges);
  std::vector<int> in(scc.scc_cnt), out(scc.scc_cnt);
  for (int i = 0; i < n; ++i) {
    for (auto &&j: edges[i]) {
      int u = scc.col[i], v = scc.col[j];
      if (u != v) {
        in[v]++, out[u]++;
        succ[u].push_back(v);
        pred[v].push_back(u);
      }
    }
  }
  for (int i = 0; i < scc.scc_cnt; ++i) {
    std::sort(succ[i].begin(), succ[i].end());
    succ[i].erase(std::unique(succ[i].begin(), succ[i].end()), succ[i].end());
    std::sort(pred[i].begin(), pred[i].end());
    pred[i].erase(std::unique(pred[i].begin(), pred[i].end()), pred[i].end());
  }
  int left = 0, right = 0;
  for (auto &&x: in) right += !x;
  std::vector<int> ret;
  for (int i = scc.scc_cnt - 1; i >= 0; --i) {
    if (in[i] == 0) --right;
    for (auto &&u: pred[i]) {
      if (out[u]++ == 0) --left;
    }
    if (!left && !right) {
      for (auto &&u: scc.SCC[i]) ret.push_back(u);
    }
    for (auto &&u: succ[i]) {
      if (--in[u] == 0) ++right;
      --out[i];
    }
    if (!out[i]) ++left;
  }
  std::sort(ret.begin(), ret.end());
  printf("%d\n", (int)ret.size());
  for (auto &&u: ret) printf("%d ", u + 1);
  puts("");
  return 0;
}

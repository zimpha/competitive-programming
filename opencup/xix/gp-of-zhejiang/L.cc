#include <cstdio>
#include <cassert>
#include <cstring>
#include <tuple>
#include <vector>

static const int N = 1e5 + 10, M = 3e5 + 10;

struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], col[N];
  int stk[N], top, scc_cnt, sz;
  void dfs(int x, const std::vector<int> edges[]) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &y: edges[x]) {
      if (!dfn[y]) {
        dfs(y, edges);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      scc_cnt++;
      do {
        col[stk[top]] = scc_cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(const std::vector<int> edges[], const std::vector<int> &nodes) {
    sz = top = scc_cnt = 0;
    for (auto x: nodes) dfn[x] = 0, col[x] = -1;
    for (auto x: nodes) {
      if (!dfn[x]) dfs(x, edges);
    }
  }
} scc;

std::vector<int> merge[M];
std::vector<int> edges[N];
int A[M], B[M];
int mark[N], cid;
int n, m;

void solve(int l, int r, std::vector<std::tuple<int, int, int>>& eids) {
  std::vector<int> nodes; cid++;
  for (auto &e: eids) {
    int a = std::get<1>(e), b = std::get<2>(e);
    if (mark[a] != cid) nodes.push_back(a);
    mark[a] = cid;
    if (mark[b] != cid) nodes.push_back(b);
    mark[b] = cid;
  }
  for (auto x: nodes) edges[x].clear();
  if (l + 1 == r) {
    for (auto &e: eids) {
      int a = std::get<1>(e), b = std::get<2>(e);
      edges[a].push_back(b);
    }
    scc.run(edges, nodes);
    for (auto &e: eids) {
      int a = std::get<1>(e), b = std::get<2>(e);
      if (scc.col[a] == scc.col[b]) merge[l].push_back(std::get<0>(e));
    }
    return;
  }
  int m = (l + r) >> 1;
  for (auto &e: eids) if (std::get<0>(e) < m) {
    int a = std::get<1>(e), b = std::get<2>(e);
    edges[a].push_back(b);
  }
  scc.run(edges, nodes);
  std::vector<std::tuple<int, int, int>> el, er;
  for (auto &e: eids) {
    int t = std::get<0>(e), a = std::get<1>(e), b = std::get<2>(e);
    if (scc.col[a] == scc.col[b]) {
      if (t < m) el.push_back(e);
    } else {
      er.emplace_back(t, scc.col[a], scc.col[b]);
    }
  }
  solve(l, m, el);
  solve(m, r, er);
}

int dsu[N], size[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  scanf("%d%d", &n, &m);
  std::vector<std::tuple<int, int, int>> eids(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &A[i], &B[i]);
    --A[i], --B[i];
    eids[i] = std::make_tuple(i, A[i], B[i]);
  }
  cid = 0;
  solve(0, m, eids);
  for (int i = 0; i < n; ++i) dsu[i] = i, size[i] = 1;
  long long ret = 0;
  for (int i = 0; i < m; ++i) {
    for (auto &e: merge[i]) {
      int u = get(A[e]), v = get(B[e]);
      if (u != v) {
        ret += 1ll * size[u] * size[v];
        dsu[u] = v;
        size[v] += size[u];
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}

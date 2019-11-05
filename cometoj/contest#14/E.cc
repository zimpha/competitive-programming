#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

static const int N = 2e5 + 10;

std::vector<std::pair<int, int>> edges[N];
std::vector<std::pair<int, int>> new_edges[N];

struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], col[N];
  int stk[N], top, cnt, sz;
  void dfs(int x) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &e: edges[x]) {
      int y = e.first;
      if (!dfn[y]) {
        dfs(y);
        low[x] = std::min(low[x], low[y]);
      } else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      cnt++;
      do {
        col[stk[top]] = cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n) {
    sz = top = cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i);
    }
  }
} scc;

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < m; ++i) {
    int x, y, h;
    scanf("%d%d%d", &x, &y, &h);
    edges[x - 1].emplace_back(y - 1, h);
  }
  scc.run(n);
  std::vector<int> mi(scc.cnt, -1), mx(scc.cnt, -1);
  std::vector<int> f(scc.cnt, -1), g(scc.cnt, -1), h(scc.cnt, 0);
  for (int u = 0; u < n; ++u) {
    for (auto &e: edges[u]) {
      int v = e.first, w = e.second, c = scc.col[u];
      if (scc.col[u] == scc.col[v]) {
        if (mi[c] == -1 || mi[c] > w) mi[c] = w;
        if (mx[c] == -1 || mx[c] < w) mx[c] = w;
      } else {
        new_edges[scc.col[u]].emplace_back(scc.col[v], w);
      }
    }
  }
  std::vector<int> deg(scc.cnt), reach(scc.cnt, 0);
  std::queue<int> queue;
  queue.push(scc.col[0]);
  reach[scc.col[0]] = 1;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto &e: new_edges[u]) if (!reach[e.first]) {
      reach[e.first] = 1;
      queue.push(e.first);
    }
  }
  for (int u = 0; u < scc.cnt; ++u) {
    for (auto &e: new_edges[u]) {
      if (reach[u] && reach[e.first]) deg[e.first]++;
    }
  }
  for (int i = 0; i < scc.cnt; ++i) {
    if (reach[i] && deg[i] == 0) queue.push(i);
  }
  assert(queue.size() == 1);
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    if (mi[u] != -1) h[u] = std::max(h[u], mx[u] - mi[u]);
    if (f[u] != -1 && mi[u] != -1) h[u] = std::max(h[u], mi[u] - f[u]);
    if (g[u] != -1 && mi[u] != -1) h[u] = std::max(h[u], g[u] - mi[u]);
    if (f[u] != -1 && mx[u] != -1) h[u] = std::max(h[u], mx[u] - f[u]);
    if (g[u] != -1 && mx[u] != -1) h[u] = std::max(h[u], g[u] - mx[u]);
    if (mi[u] != -1 && (f[u] == -1 || f[u] > mi[u])) f[u] = mi[u]; 
    if (mx[u] != -1 && (g[u] == -1 || g[u] < mx[u])) g[u] = mx[u]; 
    for (auto &e: new_edges[u]) {
      int v = e.first, w = e.second;
      int mi = w; if (f[u] != -1) mi = std::min(mi, f[u]);
      int mx = w; if (g[u] != -1) mx = std::max(mx, g[u]);
      if (f[v] == -1 || f[v] > mi) f[v] = mi;
      if (g[v] == -1 || g[v] < mx) g[v] = mx;
      h[v] = std::max(h[v], h[u]);
      if (f[u] != -1) h[v] = std::max(h[v], w - f[u]);
      if (g[u] != -1) h[v] = std::max(h[v], g[u] - w);
      if (--deg[v] == 0) queue.push(v);
    }
  }
  for (int i = 0; i < q; ++i) {
    int x;
    scanf("%d", &x);
    if (!reach[scc.col[x - 1]] || (x == 1 && mi[scc.col[0]] == -1)) puts("-1");
    else printf("%d\n", h[scc.col[x - 1]]);
  }
  return 0;
}

#include <vector>
#include <cassert>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <set>

static const int N = 100005; // 最大结点个数

class Articulation {
public:
  std::set<int> forbid[N];
  std::vector<std::pair<int, int>> key;
  int col[N], cnt = 0;
  // 传入结点个数n及各结点的出边e[]，返回双连通分量的个数cnt
  void run(int n, const std::vector<int> edges[]){
    memset(dfn, cnt = 0, sizeof(dfn[0]) * n);
    memset(low, 0, sizeof(low[0]) * n);
    for(int i = 0; i < n; ++i) {
      if(!dfn[i]) dfs(i, 1, edges);
    }
    memset(col, -1, sizeof(col[0]) * n);
    for (int i = 0; i < n; ++i) {
      if (col[i] == -1) find_cc(i, cnt++, edges);
    }
  }
private:
  int dfn[N], low[N];
  void find_cc(int x, int c, const std::vector<int> edges[]) {
    col[x] = c;
    for (auto &y: edges[x]) if (col[y] == -1 && !forbid[x].count(y)) {
      find_cc(y, c, edges);
    }
  }
  void dfs(int x, int dep, const std::vector<int> edges[]){
    int src = 0;
    dfn[x] = low[x] = dep;
    for (auto &y: edges[x]) {
      if (!dfn[y]){
        dfs(y, dep + 1, edges);
        low[x] = std::min(low[x], low[y]);
        if (low[y] > dfn[x]) {
          key.emplace_back(x, y);
          forbid[x].insert(y);
          forbid[y].insert(x);
        }
      } else if (dfn[y] != dfn[x] - 1 || src++){
        low[x] = std::min(low[x], dfn[y]);
      }
    }
  }
} tarjan;

std::vector<int> edges[N], gg[N];
int w[N], ww[N], sum[N];

void dfs(int u, int p = -1) {
  for (auto &v: gg[u]) if (v != p) {
    sum[v] = sum[u] + ww[v];
    dfs(v, u);
  }
}

int main() {
  srand(time(NULL));
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  for (int i = 0, u, v; i < m; ++i) {
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  tarjan.run(n, edges);
  for (int i = 0; i < n; ++i) {
    ww[tarjan.col[i]] += w[i];
  }
  for (auto &e: tarjan.key) {
    int u = tarjan.col[e.first];
    int v = tarjan.col[e.second];
    assert(u != v);
    gg[u].push_back(v);
    gg[v].push_back(u);
  }
  sum[0] = ww[0];
  dfs(0);
  int r = 0;
  for (int i = 0; i < tarjan.cnt; ++i) {
    if (sum[i] > sum[r]) r = i;
  }
  sum[r] = ww[r];
  dfs(r);
  for (int i = 0; i < tarjan.cnt; ++i) {
    if (sum[i] > sum[r]) r = i;
  }
  printf("%d\n", sum[r]);
  return 0;
}

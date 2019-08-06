#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const static int N = 5e3 + 10;
typedef std::vector<int> VI;

namespace DominatorTree {
  int dfn[N], pre[N], pt[N], sz;
  int semi[N], dsu[N], idom[N], best[N];
  int get(int x) {
    if (x == dsu[x]) return x;
    int y = get(dsu[x]);
    if (semi[best[x]] > semi[best[dsu[x]]]) best[x] = best[dsu[x]];
    return dsu[x] = y;
  }
  void dfs(int u, const VI succ[]) {
    dfn[u] = sz; pt[sz ++] = u;
    for (auto &v: succ[u]) if (!~dfn[v]) {
      dfs(v, succ); pre[dfn[v]] = dfn[u];
    }
  }
  void tarjan(const VI pred[], VI dom[]) {
    for (int j = sz - 1, u; u = pt[j], j > 0; -- j) {
      for (auto &tv: pred[u]) if (~dfn[tv]) {
        int v = dfn[tv]; get(v);
        if (semi[best[v]] < semi[j]) semi[j] = semi[best[v]];
      }
      dom[semi[j]].push_back(j);
      int x = dsu[j] = pre[j];
      for (auto &z: dom[x]) {
        get(z);
        if (semi[best[z]] < x) idom[z] = best[z];
        else idom[z] = x;
      }
      dom[x].clear();
    }
    for (int i = 1; i < sz; ++ i) {
      if (semi[i] != idom[i]) idom[i] = idom[idom[i]];
      dom[idom[i]].push_back(i);
    }
  }
  void build(int n, int s, const VI succ[], const VI pred[], VI dom[]) {
    for (int i = 0; i < n; ++ i) {
      dfn[i] = -1; dom[i].clear();
      dsu[i] = best[i] = semi[i] = i;
    }
    sz = 0; dfs(s, succ); tarjan(pred, dom);
  }
}

VI succ[N], pred[N], dom[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    succ[u].push_back(v);
    pred[v].push_back(u);
  }
  DominatorTree::build(n, 0, succ, pred, dom);
  std::vector<int> ret;
  for (int i = 0; i < n; ++i) if (!dom[i].empty()) {
    ret.push_back(DominatorTree::pt[i]);
  }
  std::sort(ret.begin(), ret.end());
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x + 1);
  puts("");
  return 0;
}

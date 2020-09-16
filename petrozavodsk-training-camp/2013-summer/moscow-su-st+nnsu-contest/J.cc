#include <vector>
#include <cstdio>

const static int N = 3e5 + 10;

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
  freopen("redundant.in", "r", stdin);
  freopen("redundant.out", "w", stdout);
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  --s;
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    succ[a].push_back(n + i); succ[n + i].push_back(b);
    pred[n + i].push_back(a); pred[b].push_back(n + i);
  }
  DominatorTree::build(n + m, s, succ, pred, dom);
  std::vector<int> ret;
  for (int i = 0; i < m; ++i) {
    int id = DominatorTree::dfn[i + n];
    if (id == -1 || dom[id].empty()) ret.push_back(i + 1);
  }
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x);
  puts("");
  return 0;
}

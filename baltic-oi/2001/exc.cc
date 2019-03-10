#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

struct TwoSAT {
  static const int N = 200000 + 10;
  std::vector<int> edges[N];
  std::vector<int> scc[N];
  int low[N], dfn[N], col[N];
  int stk[N], top, cnt, sz;
  int sol[N], n;
  void init(int n) {
    this->n = n;
    for (int i = 0; i < n * 2; ++i) {
      edges[i].clear();
    }
  }
  void dfs(int x) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &y: edges[x]) {
      if (!dfn[y]) {
        dfs(y);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      scc[cnt++].clear();
      do {
        scc[cnt - 1].push_back(stk[top]);
        col[stk[top]] = cnt - 1;
      } while (stk[top--] != x);
    }
  }
  bool solve() {
    sz = top = cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n * 2);
    memset(col, -1, sizeof(*col) * n * 2);
    for (int i = 0; i < n * 2; ++i) {
      if (!dfn[i]) dfs(i);
    }
    for (int i = 0; i < n * 2; i += 2) {
      if (col[i] == col[i ^ 1]) return false;
      sol[i] = -1;
    }
    for (int i = 0; i < cnt; ++i) {
      int val = 1;
      for (auto &&x: scc[i]) {
        if (sol[x] == 0) val = 0;
        for (auto &&y: edges[x]) {
          if (sol[y] == 0) val = 0;
        }
        if (val == 0) break;
      }
      for (auto &&x: scc[i]) {
        sol[x] = val;
        sol[x ^ 1] = !val;
      }
    }
    return true;
  }
  void add_clause(int x, int xv, int y, int yv) {//x=xv or y=yv
    x = x << 1 | xv, y = y << 1 | yv;
    add_edge(x ^ 1, y);
    add_edge(y ^ 1, x);
  }
  void add_var(int x, int xv) { // x = xv
    x = x << 1 | xv;
    edges[x ^ 1].push_back(x);
  }
  void add_edge(int x, int y) {
    edges[x].push_back(y);
  }
} sat;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  sat.init(m);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    int xv = x < 0;
    int yv = y < 0;
    x = std::abs(x);
    y = std::abs(y);
    sat.add_clause(x - 1, xv, y - 1, yv);
  }
  if (!sat.solve()) puts("NO");
  else {
    std::vector<int> result;
    for (int i = 0; i < m; ++i) {
      if (sat.sol[i * 2] == 1) result.push_back(i + 1);
    }
    printf("%d\n", (int)result.size());
    for (auto &&x: result) printf("%d ", x);
    puts("");
  }
  return 0;
}

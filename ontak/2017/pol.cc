#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

std::vector<int> edges[N];
int low[N], dfn[N], stk[N], col[N];
int top, scc_cnt, sz;

void dfs(int x) {
  low[x] = dfn[x] = ++sz;
  stk[++top] = x;
  for (auto &&y: edges[x]) {
    if (!dfn[y]) {
      dfs(y);
      low[x] = std::min(low[x], low[y]);
    } else if (col[y] == -1) {
      low[x] = std::min(low[x], dfn[y]);
    }
  }
  if (low[x] == dfn[x]) {
    do {
      col[stk[top]] = scc_cnt;
    } while (stk[top--] != x);
    scc_cnt++;
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
  }
  memset(col, -1, sizeof(*col) * n);
  for (int i = 0; i < n; ++i) {
    if (!dfn[i]) dfs(i);
  }
  std::vector<int> deg(scc_cnt);
  for (int i = 0; i < n; ++i) {
    for (auto &&u: edges[i]) {
      if (col[i] != col[u]) deg[col[u]]++;
    }
  }
  std::vector<int> candidate;
  for (int i = 0; i < scc_cnt; ++i) {
    if (deg[i] == 0) candidate.push_back(i);
  }
  if (candidate.size() != 1) puts("0");
  else {
    int root = candidate[0];
    candidate.clear();
    for (int i = 0; i < n; ++i) {
      if (col[i] == root) candidate.push_back(i + 1);
    }
    printf("%d\n", (int)candidate.size());
    for (size_t i = 0; i < candidate.size(); ++i) {
      if (i) putchar(' ');
      printf("%d", candidate[i]);
    }
    puts("");
  }
  return 0;
}

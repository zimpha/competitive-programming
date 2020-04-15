#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>

const int M = 100, N = 5000 + 10;

char s[M][M];
int rid[M][M], cid[M][M];
std::vector<int> edges[N];
bool mark[N][N];

void dfs(int u, bool *mark) {
  if (mark[u]) return;
  mark[u] = true;
  for (auto &v: edges[u]) dfs(v, mark);
}

struct TwoSAT {
  std::vector<int> edges[N];
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
      cnt++;
      do {
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
    }
    return true;
  }
  void add_edge(int x, int y) {
    edges[x].push_back(y);
  }
} two_sat;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }
  memset(rid, -1, sizeof(rid));
  memset(cid, -1, sizeof(cid));
  int id = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ) {
      if (s[i][j] == '#') ++j;
      else {
        while (j < m && s[i][j] != '#') rid[i][j++] = id;
        id++;
      }
    }
  }
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ) {
      if (s[i][j] == '#') ++i;
      else {
        while (i < n && s[i][j] != '#') cid[i++][j] = id;
        id++;
      }
    }
  }
  int src = id++;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (s[i][j] != '#') {
      if (s[i][j] == 'O') {
        edges[src].push_back(rid[i][j]);
        edges[src].push_back(cid[i][j]);
      }
      if (j == 0 || s[i][j - 1] == '#') edges[rid[i][j]].push_back(cid[i][j]);
      if (j == m - 1 || s[i][j + 1] == '#') edges[rid[i][j]].push_back(cid[i][j]);
      if (i == 0 || s[i - 1][j] == '#') edges[cid[i][j]].push_back(rid[i][j]);
      if (i == n - 1 || s[i + 1][j] == '#') edges[cid[i][j]].push_back(rid[i][j]);
    }
  }
  for (int i = 0; i < id; ++i) dfs(i, mark[i]);
  two_sat.init(src);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (s[i][j] == '*') {
      two_sat.add_edge(rid[i][j] * 2, cid[i][j] * 2 + 1);
      two_sat.add_edge(cid[i][j] * 2, rid[i][j] * 2 + 1);
    }
  }
  for (int i = 0; i < src; ++i) if (!mark[src][i]) {
    two_sat.add_edge(i * 2 + 1, i * 2);
  }
  for (int i = 0; i < src; ++i) {
    for (int j = i + 1; j < src; ++j) {
      if (!mark[i][j] && !mark[j][i]) {
        two_sat.add_edge(i * 2 + 1, j * 2);
        two_sat.add_edge(j * 2 + 1, i * 2);
      }
    }
  }
  bool valid = two_sat.solve();
  if (valid) puts("YES");
  else puts("NO");
  return 0;
}

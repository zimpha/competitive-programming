#include <cstdio>
#include <vector>

const int N = 2e5 + 10;
const int mod = 998244353;

std::vector<int> edges[N];
int col[N], mark[N], cnt;

void dfs0(int u) {
  mark[u] = 1; ++cnt;
  for (auto &v: edges[u]) {
    if (!mark[v]) dfs0(v);
  }
}

bool dfs(int u, int c) {
  if (col[u] != -1) return col[u] == c;
  col[u] = c;
  for (auto &v: edges[u]) {
    if (!dfs(v, c ^ 1)) return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      col[i] = -1;
      mark[i] = 0;
      edges[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) if (!mark[i]) {
      cnt = 0;
      dfs0(i);
      if (!dfs(i, 0)) m -= cnt;
      else m -= cnt - 1;
    }
    int ret = 1;
    for (int i = 0; i < m; ++i) ret = ret * 5ll % mod;
    printf("%d\n", ret);
  }
  return 0;
}

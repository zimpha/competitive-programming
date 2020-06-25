#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

std::vector<std::pair<int, int>> edges[N];
int64 up[N], sub[N];
int64 ret;

void dfs(int u, int p = -1) {
  if (edges[u].size() == 1) {
    up[u] = 1e9;
    sub[u] = 0;
    return;
  }
  std::vector<int> w;
  for (auto &e: edges[u]) if (p != e.first) {
    int v = e.first;
    dfs(v, u);
    if (e.second < up[v]) {
      int64 x = std::min((up[v] - e.second + 1) / 2, sub[v]);
      sub[v] -= x; up[v] -= 2 * x; ret += x;
    }
    up[v] = std::min<int64>(up[v], e.second);
  }
  up[u] = sub[u] = 0;
  for (auto &e: edges[u]) if (p != e.first) {
    int v = e.first;
    int64 t_sub = sub[u];
    int64 x = std::min(up[u], up[v]);
    sub[u] = x + std::min((up[u] - x) / 2, t_sub) + std::min((up[v] - x) / 2, sub[v]);
    --x;
    sub[u] = std::max(sub[u], x + std::min((up[u] - x) / 2, t_sub) + std::min((up[v] - x) / 2, sub[v]));
    up[u] += up[v];
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      --u, --v;
      edges[u].emplace_back(v, w);
      edges[v].emplace_back(u, w);
    }
    if (n == 2) {
      printf("%d\n", edges[0][0].second);
      continue;
    }
    int root = 0;
    for (int i = 0; i < n; ++i) {
      if (edges[i].size() > 1) root = i;
    }
    ret = 0;
    dfs(root);
    printf("%lld\n", ret + sub[root]);
  }
  return 0;
}

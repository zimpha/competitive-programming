#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  freopen("cycles.in", "r", stdin);
  freopen("cycles.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(m), b(m), deg(n);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    deg[--a[i]]++;
    deg[--b[i]]++;
  }
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < m; ++i) {
    if (deg[a[i]] < deg[b[i]] || (deg[a[i]] == deg[b[i]] && a[i] < b[i])) edges[a[i]].push_back(b[i]);
    else edges[b[i]].push_back(a[i]);
  }
  std::vector<bool> mark(n);
  int ret = 0;
  for (int u = 0; u < n; ++u) {
    for (auto &v: edges[u]) mark[v] = 1;
    for (auto &v: edges[u]) {
      for (auto &w: edges[v]) ret += mark[w];
    }
    for (auto &v: edges[u]) mark[v] = 0;
  }
  printf("%d\n", ret);
  return 0;
}

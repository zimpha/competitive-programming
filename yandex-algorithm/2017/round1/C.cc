#include <bits/stdc++.h>

const int N = 200000 + 10;
std::vector<int> G[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> mark(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    std::set<int> s;
    for (auto &&v: G[i]) if (v < i) {
      s.insert(mark[v]);
    }
    int k = 1;
    while (s.count(k)) ++k;
    mark[i] = k;
    ret = std::max(ret, k);
  }
  printf("%d\n", ret);
  for (int i = 1; i <= n; ++i) {
    printf("%d ", mark[i]);
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::pair<int, int>> a(n);
  std::vector<std::pair<int, int>> b(m);
  std::vector<int> xs;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    xs.push_back(a[i].first);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &b[i].first, &b[i].second);
  }
  std::sort(xs.begin(), xs.end());
  m = xs.size() + 1;
  std::vector<int> value(m + 2);
  for (auto &x: a) {
    int p = std::lower_bound(xs.begin(), xs.end(), x.first) - xs.begin();
    value[p + 1] = x.second;
  }
  std::vector<std::vector<std::pair<int, int>>> edges(m + 1);
  for (size_t i = 0; i < b.size(); ++i) {
    int u = std::lower_bound(xs.begin(), xs.end(), b[i].first) - xs.begin();
    int v = std::upper_bound(xs.begin(), xs.end(), b[i].second) - xs.begin(); 
    edges[u].emplace_back(v, i);
    edges[v].emplace_back(u, i);
  }

  std::vector<int> ret, mark(m + 1);
  std::function<int(int)> dfs = [&](int u) {
    if (mark[u]) return 0;
    mark[u] = 1;
    int cnt = 0;
    for (auto &e: edges[u]) {
      if (dfs(e.first)) ret.push_back(e.second), cnt ^= 1;
    }
    if (value[u] ^ value[u + 1]) cnt ^= 1;
    return cnt;
  };

  for (int i = 0; i <= m; ++i) {
    int r = dfs(i);
    if (r == 1) { puts("-1"); return 0; }
  }
  std::sort(ret.begin(), ret.end());
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x + 1);
  puts("");
  return 0;
}

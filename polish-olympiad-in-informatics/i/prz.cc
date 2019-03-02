#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

bool solve(const std::vector<int>& t, const std::vector<std::vector<int>>& edges, std::vector<int64>& dp) {
  int n = t.size();
  std::vector<int> queue;
  std::vector<int> deg(n);
  for (int i = 0; i < n; ++i) {
    for (auto &&u: edges[i]) deg[u]++;
  }
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) {
      queue.push_back(i);
      dp[i] = 0;
    }
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    dp[u] += t[u];
    for (auto &&v: edges[u]) {
      dp[v] = std::max(dp[v], dp[u]);
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  return queue.size() == n;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> t(n);
  std::vector<std::vector<int>> pred(n), succ(n);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d%d", &t[i], &m);
    for (int j = 0; j < m; ++j) {
      int x;
      scanf("%d", &x);
      --x;
      succ[x].push_back(i);
      pred[i].push_back(x);
    }
  }
  std::vector<int64> f(n), g(n);
  if (!solve(t, succ, f)) {
    puts("CYKL");
    return 0;
  }
  solve(t, pred, g);
  auto best = *std::max_element(f.begin(), f.end());
  printf("%lld\n", best);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (f[x - 1] + g[x - 1] + y - t[x - 1] > best) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

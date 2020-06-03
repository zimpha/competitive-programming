#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<int>> edges(n);
  std::vector<int> deg(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    edges[x].push_back(y);
    deg[y]++;
  }
  std::vector<int> dp(n);
  std::queue<int> queue;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) queue.push(i);
  }
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto &&v: edges[u]) {
      dp[v] = std::max(dp[v], dp[u] + 1);
      if (--deg[v] == 0) queue.push(v);
    }
  }
  printf("%d\n", *std::max_element(dp.begin(), dp.end()));
  return 0;
}

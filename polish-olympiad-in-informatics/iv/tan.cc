#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int d, n;
  scanf("%d%d", &d, &n);
  std::vector<int> dis(n + 2), cost(n + 2);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &dis[i], &cost[i]);
  dis[0] = 0;
  dis[n + 1] = d;
  std::vector<std::pair<int, int>> f(n + 2), g(n + 2);
  std::vector<int> from_f(n + 2), from_g(n + 2);
  f[0] = g[0] = {0, 0};
  for (int i = 1; i <= n + 1; ++i) {
    f[i] = g[i] = {-1, -1};
    for (int j = 0; j < i; ++j) if (dis[i] - dis[j] <= 800) {
      if (f[i].first == -1 || f[i].first > f[j].first + cost[i] || (f[i].first == f[j].first + cost[i] && f[i].second > f[j].second + 1)) {
        f[i].first = f[j].first + cost[i];
        f[i].second = f[j].second + 1;
        from_f[i] = j;
      }
      if (g[i].first == -1 || g[i].first > g[j].first + 1 || (g[i].first == g[j].first + 1 && g[i].second > g[j].second + cost[i])) {
        g[i].first = g[j].first + 1;
        g[i].second = g[j].second + cost[i];
        from_g[i] = j;
      }
    }
  }
  std::vector<int> plan_f;
  for (int i = from_f[n + 1]; i != 0; i = from_f[i]) {
    plan_f.push_back(dis[i]);
  }
  std::reverse(plan_f.begin(), plan_f.end());
  for (auto &&x: plan_f) printf("%d ", x);
  puts("");
  std::vector<int> plan_g;
  for (int i = from_g[n + 1]; i != 0; i = from_g[i]) {
    plan_g.push_back(dis[i]);
  }
  std::reverse(plan_g.begin(), plan_g.end());
  for (auto &&x: plan_g) printf("%d ", x);
  puts("");
  return 0;
}

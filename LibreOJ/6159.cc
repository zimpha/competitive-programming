#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> edges(n - 1);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &edges[i - 1].first, &edges[i - 1].second);
    --edges[i - 1].first;
    --edges[i - 1].second;
  }
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::map<int, std::vector<int>> mp;
  for (int i = 0; i < n - 1; ++i) {
    int g = gcd(a[edges[i].first], a[edges[i].second]);
    for (int d = 2; d * d <= g; ++d) {
      if (g % d == 0) {
        mp[d].push_back(i);
        while (g % d == 0) g /= d;
      }
    }
    if (g > 1) mp[g].push_back(i);
  }
  std::vector<std::vector<int>> g(n);
  std::vector<bool> mark(n);
  std::vector<int> dis(n);
  auto solve = [&edges, &g, &mark, &dis](const std::vector<int> &edge_indices) {
    std::vector<int> pts;
    for (auto &&e: edge_indices) {
      int x = edges[e].first;
      int y = edges[e].second;
      g[x].clear();
      g[y].clear();
      mark[x] = mark[y] = true;
      dis[x] = dis[y] = -1;
      pts.push_back(x);
      pts.push_back(y);
    }
    for (auto &&e: edge_indices) {
      int x = edges[e].first;
      int y = edges[e].second;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    int ret = 0;
    for (auto &&e: pts) if (mark[e]) {
      std::vector<int> queue = {e};
      dis[e] = 0;
      for (size_t i = 0; i < queue.size(); ++i) {
        int u = queue[i];
        for (auto &&v: g[u]) if (dis[v] == -1) {
          dis[v] = dis[u] + 1;
          queue.push_back(v);
        }
      }
      int x = e;
      for (auto &&y: queue) {
        if (dis[y] > dis[x]) x = y;
      }
      for (auto &&y: queue) {
        dis[y] = -1;
        mark[y] = false;
      }
      queue = {x};
      dis[x] = 0;
      for (size_t i = 0; i < queue.size(); ++i) {
        int u = queue[i];
        for (auto &&v: g[u]) if (dis[v] == -1) {
          dis[v] = dis[u] + 1;
          queue.push_back(v);
        }
      }
      for (auto &&y: queue) {
        ret = std::max(ret, dis[y]);
      }
    }
    return ret + 1;
  };
  int ret = 1;
  for (auto &&e: mp) {
    ret = std::max(ret, solve(e.second));
  }
  printf("%d\n", ret);
  return 0;
}

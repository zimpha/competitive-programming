#include <cstdio>
#include <cassert>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  assert(m == n - 1);
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  int k;
  scanf("%d", &k);
  std::vector<int> worm(k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &worm[i]);
    --worm[i];
  }
  std::vector<int> dis(n, -1);
  std::vector<int> queue = {worm[0]};
  dis[worm[0]] = 0;
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &v: edges[u]) if (dis[v] == -1) {
      dis[v] = dis[u] + 1;
      queue.push_back(v);
    }
  }
  int best = -1;
  for (auto &x: worm) {
    if (dis[x] & 1) {
      puts("NIE");
      return 0;
    }
    if (best == -1 || dis[best] < dis[x]) best = x;
  }
  dis.assign(n, -1);
  queue = {best};
  dis[best] = 0;
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &v: edges[u]) if (dis[v] == -1) {
      dis[v] = dis[u] + 1;
      queue.push_back(v);
    }
  }
  best = -1;
  for (auto &x: worm) {
    if (best == -1 || dis[best] < dis[x]) best = x;
  }
  printf("%d\n", dis[best] / 2);
  return 0;
}

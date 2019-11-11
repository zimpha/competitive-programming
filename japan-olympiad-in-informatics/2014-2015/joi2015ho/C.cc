#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

std::vector<std::pair<int, int>> edges[N];

int main() {
  int n, m, c;
  scanf("%d%d%d", &n, &m, &c);
  int64 sum = 0;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
    sum += w;
  }
  std::priority_queue<std::pair<int64, int>> pq;
  std::vector<int64> dis(n, -1);
  dis[0] = 0;
  pq.emplace(0, 0);
  while (!pq.empty()) {
    int64 d = -pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (dis[u] < d) continue;
    for (auto &e: edges[u]) {
      int v = e.first;
      int64 w = d + e.second;
      if (dis[v] == -1 || dis[v] > w) {
        dis[v] = w;
        pq.emplace(-w, v);
      }
    }
  }
  std::vector<int> idx(n), pos(n);
  for (int i = 0; i < n; ++i) idx[i] = i;
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return dis[x] < dis[y];
  });
  for (int i = 0; i < n; ++i) pos[idx[i]] = i;
  int64 ret = sum;
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && dis[idx[i]] == dis[idx[j]]; ++j) {
      for (auto &e: edges[idx[j]]) {
        if (pos[e.first] < j) sum -= e.second;
      }
    }
    ret = std::min(ret, sum + dis[idx[i]] * c);
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int64, int>;

const int N = 2e5 + 10;

std::map<int, int> id[N];
std::vector<int> use[N];
int n, m, k, s, t, sz;

int main() {
  scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
  std::vector<int> a(m), b(m), c(m);
  id[0][s] = 0;
  id[n - 1][t] = 1;
  sz = 2;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
    --a[i];
    if (!id[a[i]].count(b[i])) id[a[i]][b[i]] = sz++;
    if (!id[a[i] + 1].count(c[i])) id[a[i] + 1][c[i]] = sz++;
  }
  std::vector<std::vector<pii>> edges(sz);
  for (int i = 0; i < m; ++i) {
    int u = id[a[i]][b[i]];
    int v = id[a[i] + 1][c[i]];
    edges[u].emplace_back(v, 0);
  }
  for (int i = 0; i < n; ++i) {
    int u = -1, d = -1;
    for (auto &&e: id[i]) {
      if (u != -1) {
        int v = e.second;
        d = e.first - d;
        edges[u].emplace_back(v, d);
        edges[v].emplace_back(u, d);
      }
      std::tie(d, u) = e;
    }
  }
  std::vector<int64> dis(sz, -1);
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  pq.emplace(0, 0);
  dis[0] = 0;
  while (!pq.empty()) {
    auto now = pq.top();
    pq.pop();
    int u = now.second;
    if (dis[u] < now.first) continue;
    for (auto &&e: edges[u]) {
      int v = e.first, w = e.second;
      if (dis[v] == -1 || dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(dis[v], v);
      }
    }
  }
  printf("%lld\n", dis[1]);
  return 0;
}

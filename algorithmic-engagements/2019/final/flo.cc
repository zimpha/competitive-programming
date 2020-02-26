#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>

const int N = 2e3 + 10;
const int inf = 1e9;

using uint64 = unsigned long long;
using uint = unsigned int;

std::vector<std::pair<int, int>> succ[N];
std::vector<std::pair<int, int>> pred[N];
int dist[N][N], order[N];
int ns, n, m;

struct Bitset {
  uint64 u[32];
  void set(uint x) { u[x / 64] |= uint64(1) << (x % 64); }
  bool test(uint x) const { return u[x / 64] >> (x % 64) & 1; }
  Bitset& operator &= (const Bitset& rhs) {
    for (int i = 0; i < ns; ++i) u[i] &= rhs.u[i];
    return *this;
  }
  Bitset& operator |= (const Bitset& rhs) {
    for (int i = 0; i < ns; ++i) u[i] |= rhs.u[i];
    return *this;
  }
  Bitset operator & (const Bitset& rhs) const {
    return Bitset(*this) &= rhs;
  }
  bool any() const {
    for (int i = 0; i < ns; ++i) {
      if (u[i]) return true;
    }
    return false;
  }
  void reset() {
    for (int i = 0; i < ns; ++i) u[i] = 0;
  }
};

Bitset f[N], g[N], on[N];

void dijkstra(int s, int* d) {
  for (int i = 0; i < n; ++i) d[i] = inf;
  d[s] = 0;
  std::priority_queue<std::pair<int, int>> pq;
  pq.emplace(-d[s], s);
  while (!pq.empty()) {
    int u = pq.top().second;
    int w = -pq.top().first;
    pq.pop();
    if (d[u] < w) continue;
    for (auto &e: succ[u]) {
      int ww = w + e.second, v = e.first;
      if (d[v] > ww) {
        d[v] = ww;
        pq.emplace(-ww, v);
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  ns = (n + 64) / 64;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    succ[u - 1].emplace_back(v - 1, w);
    pred[v - 1].emplace_back(u - 1, w);
  }
  for (int i = 0; i < n; ++i) dijkstra(i, dist[i]);
  for (int u = 0; u < n; ++u) {
    f[u].set(u); g[u].set(u);
    for (auto &e: succ[u]) {
      int v = e.first, w = e.second;
      if (w == dist[u][v]) f[u].set(v), g[v].set(u);
    }
  }
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) order[y] = y;
    for (int y = 0; y < n; ++y) on[y].reset();
    std::sort(order, order + n, [&](int a, int b) {
      return dist[x][a] < dist[x][b];
    });
    for (int i = 0; i < n; ++i) {
      int u = order[i];
      on[u].set(u); on[u].set(x);
      for (auto &e: pred[u]) {
        int v = e.first, w = e.second;
        if (dist[x][v] + w == dist[x][u]) on[u] |= on[v];
      }
    }
    for (int y = 0; y < n; ++y) {
      auto tmp = f[x];
      tmp &= g[y];
      tmp &= on[y];
      if (tmp.any()) f[x].set(y), g[y].set(x);
    }
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) order[j] = j;
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] == inf) continue;
      ret += !f[i].test(j);
    }
  }
  printf("%d\n", ret);
  return 0;
}

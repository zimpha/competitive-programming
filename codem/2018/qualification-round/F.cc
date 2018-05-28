#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

const int N = 2e3 + 10, M = 2e5 + N;

std::vector<std::pair<int, int>> edges[N];
std::vector<int> bucket[M];
int n, m;

void reverse(int u, int v, int w) {
  for (auto &e: edges[u]) {
    if (e.first == v && e.second == w) {
      edges[v].emplace_back(u, e.second);
      std::swap(e, edges[u].back());
      edges[u].pop_back();
      return;
    }
  }
}

int bfs(int S, int T, int mw) {
  static int dis[N], prev[N], weight[N];
  for (int i = 0; i < mw; ++i) {
    bucket[i].clear();
  }
  for (int i = 0; i <= T; ++i) dis[i] = mw;
  dis[S] = 0;
  bucket[0].emplace_back(S);
  bool find = false;
  for (int level = 0; level < mw && !find; ++level) {
    while (!bucket[level].empty()) {
      int u = bucket[level].back();
      bucket[level].pop_back();
      if (u == T) find = true;
      if (find) break;
      if (level > dis[u]) continue;
      for (auto &&e: edges[u]) {
        int v = e.first, w = std::max(dis[u], e.second);
        if (w < dis[v]) {
          dis[v] = w;
          weight[v] = e.second;
          prev[v] = u;
          bucket[w].emplace_back(v);
        }
      }
    }
  }
  if (dis[T] == mw) return -1;
  for (int u = T; u != S; u = prev[u]) {
    reverse(prev[u], u, weight[u]);
  }
  return dis[T];
}

void solve() {
  scanf("%d%d", &n, &m);
  std::vector<int> xs(m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v + n, w);
    xs[i] = w;
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (int i = 0; i < n; ++i) {
    for (auto &&e: edges[i]) {
      e.second = std::lower_bound(xs.begin(), xs.end(), e.second) - xs.begin();
    }
  }
  int S = n + n, T = S + 1;
  for (int i = 0; i < n; ++i) {
    edges[S].emplace_back(i, 0);
    edges[i + n].emplace_back(T, 0);
  }
  for (int it = 0; it < n; ++it) {
    if (it) putchar(' ');
    int ret = bfs(S, T, xs.size());
    if (ret != -1) ret = xs[ret];
    printf("%d", ret);
  }
  puts("");
}

int main() {
  solve();
  return 0;
}

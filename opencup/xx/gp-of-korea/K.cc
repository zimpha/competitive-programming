#include <cstdio>
#include <vector>

using int64 = long long;

const int N = 3e5 + 10;
const int64 inf = 1ll << 60;

struct Tree {
  std::vector<std::pair<int, int>> edges[N];
  std::vector<std::pair<int, int64>> entries[N];
  std::vector<std::pair<int, int64>> subtree[N];
  bool first;

  void build(int n, bool first) {
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      edges[u - 1].emplace_back(v - 1, w);
      edges[v - 1].emplace_back(u - 1, w);
    }
    this->first = first;
    work(0, n);
  }

  int size[N], mark[N];
  int mins, root, tot;

  void get_centroid(int u, int p = -1) {
    int mx = 0; size[u] = 1;
    for (auto &e: edges[u]) {
      int v = e.first;
      if (v == p || mark[v]) continue;
      get_centroid(v, u);
      size[u] += size[v];
      mx = std::max(mx, size[v]);
    }
    mx = std::max(mx, tot - size[u]);
    if (mx < mins) mins = mx, root = u;
  }

  void get_dist(int u, int64 d, int p = -1) {
    if (first) subtree[root].emplace_back(u, d);
    else entries[u].emplace_back(root, d);
    size[u] = 1;
    for (auto &e: edges[u]) {
      int v = e.first, w = e.second;
      if (v == p || mark[v]) continue;
      get_dist(v, d + w, u);
      size[u] += size[v];
    }
  }

  void work(int u, int total) {
    tot = total, mins = tot * 2;
    get_centroid(u);
    mark[u = root] = 1;
    if (first) subtree[u].reserve(total);
    get_dist(u, 0);
    for (auto &e: edges[u]) {
      int v = e.first;
      if (!mark[v]) work(v, size[v]);
    }
  }
} T1, T2;

std::pair<int64, int> best1[N], best2[N];
int64 ret[N];
int count[N];

int main() {
  int n;
  scanf("%d", &n);
  T1.build(n, 1);
  T2.build(n, 0);
  for (int i = 0; i < n; ++i) ret[i] = inf;
  for (int i = 0; i < n; ++i) count[i] = -1;
  for (int i = 0; i < n; ++i) {
    for (auto &e1: T1.subtree[i]) {
      for (auto &e2: T2.entries[e1.first]) {
        int root = e2.first;
        if (count[root] != i) {
          count[root] = i;
          best1[root] = {inf, inf};
          best2[root] = {inf, inf};
        }
        std::pair<int64, int> value = {e1.second + e2.second, e1.first};
        if (value < best1[root]) std::swap(best1[root], value);
        if (value < best2[root]) std::swap(best2[root], value);
      }
    }
    for (auto &e1: T1.subtree[i]) {
      int u = e1.first;
      for (auto &e2: T2.entries[e1.first]) {
        int root = e2.first;
        int64 w = e1.second + e2.second;
        if (best1[root].second != u) ret[u] = std::min(ret[u], w + best1[root].first);
        if (best2[root].second != u) ret[u] = std::min(ret[u], w + best2[root].first);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

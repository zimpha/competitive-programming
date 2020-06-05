#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

std::vector<std::pair<int, int>> edges[N];

int size[N], mark[N], w[N], total;
double sum[N];

std::pair<int, int> centroid(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  std::pair<int, int> ret{-1, -1};
  for (auto &e: edges[u]) {
    int v = e.first;
    if (v == p || mark[v]) continue;
    auto t = centroid(v, u);
    mx = std::max(mx, size[v]);
    size[u] += size[v];
    if (ret.first == -1 || t.first < ret.first) ret = t;
  }
  mx = std::max(mx, total - size[u]);
  if (ret.first == -1 || mx < ret.first) ret = {mx, u};
  return ret;
}

double dfs(int u, int p = -1, int d = 0) {
  sum[u] = w[u] * sqrt(d);
  double ret = sum[u] * d;
  for (auto &e: edges[u]) if (e.first != p) {
    ret += dfs(e.first, u, d + e.second);
    sum[u] += sum[e.first];
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u - 1].emplace_back(v - 1, w);
    edges[v - 1].emplace_back(u - 1, w);
  }
  int go = 0, ret = -1;
  double best = -1;
  for (total = n; ; ) {
    int u = centroid(go).second;
    double now = dfs(u);
    mark[u] = true;
    centroid(u);
    if (best == -1 || best > now) {
      best = now;
      ret = u;
    }
    bool found = false;
    for (auto &e: edges[u]) {
      int v = e.first;
      if (mark[v]) continue;
      if (sum[v] * 2 > sum[u]) {
        go = v;
        total = size[v];
        found = true;
        break;
      }
    }
    if (!found) break;
  }
  printf("%d %.10f\n", ret + 1, best);
  return 0;
}

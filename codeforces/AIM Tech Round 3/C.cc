#include <bits/stdc++.h>

const int N = 400000 + 10;

std::vector<int> G[N];
std::pair<int, int> best[N][2];
int n, sz[N], down[N], up[N];
int ret[N];

void dfs_down(int u, int p = -1) {
  sz[u] = 1;
  down[u] = -1;
  for (auto &&v: G[u]) if (v != p) {
    dfs_down(v, u);
    sz[u] += sz[v];
    down[u] = std::max(down[u], down[v]);
  }
  if (sz[u] <= n / 2) {
    down[u] = std::max(down[u], sz[u]);
  }
}

void dfs_up(int u, int p = -1) {
  best[u][0] = best[u][1] = {-1, -1};
  for (auto &&v: G[u]) if (v != p) {
    if (down[v] >= best[u][0].first) {
      best[u][1] = best[u][0];
      best[u][0] = {down[v], v};
    } else if (down[v] > best[u][1].first) {
      best[u][1] = {down[v], v};
    }
  }
  for (auto &&v: G[u]) if (v != p) {
    up[v] = std::max(up[u], best[u][best[u][0].second == v].first);
    if (n - sz[v] <= n / 2) {
      up[v] = std::max(up[v], n - sz[v]);
    }
    dfs_up(v, u);
  }
  int mx = n - sz[u], from = p, val = 0;
  if (p != -1) {
    val = std::max(up[p], best[p][best[p][0].second == u].first);
    if (mx <= n / 2) {
      val = std::max(val, mx);
    }
  }
  for (auto &&v: G[u]) if (v != p) {
    if (sz[v] > mx) {
      mx = sz[v];
      from = v;
    }
  }
  int sub = from == p ? val : down[from];
  if (mx - sub <= n / 2) ret[u] = 1;
}

void run() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs_down(0);
  dfs_up(0);
  for (int i = 0; i < n; ++i) {
    std::cout << ret[i] << " \n"[i == n - 1];
  }
}

int main() {
  run();
  return 0;
}

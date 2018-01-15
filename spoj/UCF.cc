#include <cstdio>
#include <vector>
#include <queue>

using pii = std::pair<int, int>;

constexpr int N = 500 + 10;
constexpr int mod = 1e9 + 7;

std::vector<int> edges[N];
int binom[N][N], cost[N];
bool leaf[N], branch[N];

pii dfs(int u, int p = -1) {
  int size = 0, ways = 1;
  for (auto &&v: edges[u]) if (v != p && branch[v]) {
    auto t = dfs(v, u);
    ways = 1ll * ways * t.second % mod;
    size += t.first;
    ways = 1ll * ways * binom[size][t.first] % mod;
  }
  return {size + 1, ways};
}

int main() {
  for (int i = 0; i < N; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", cost + i);
      edges[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      edges[u].emplace_back(v);
      edges[v].emplace_back(u);
    }
    for (int i = 0; i < n; ++i) {
      leaf[i] = edges[i].size() == 1;
    }
    int ways = -1, min_size = -1, min_cost = -1;
    if (m == 1) {
      min_size = 1;
      min_cost = std::min(cost[0], cost[1]);
      if (cost[0] == cost[1]) ways = 2;
      else ways = 1;
    } else if (m == n - 1) {
      min_size = 1, min_cost = 0, ways = 0;
      for (int i = 0; i < n; ++i) {
        branch[i] = !leaf[i];
        min_cost += branch[i] * cost[i];
      }
      for (int i = 0; i < n; ++i) if (branch[i]) {
        ways += dfs(i).second;
        ways %= mod;
      }
    } else {
      std::vector<int> deg(n);
      std::queue<int> queue;
      for (int i = 0; i < n; ++i) {
        if (leaf[i]) queue.emplace(i);
        else deg[i] = edges[i].size();
        branch[i] = 0;
      }
      std::vector<bool> mark(n);
      while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (auto &&v: edges[u]) if (deg[v] > 1) {
          mark[v] = true;
          if (--deg[v] == 1) {
            queue.emplace(v);
          }
        }
        if (!leaf[u]) {
          branch[u] = true;
        }
      }
      std::vector<int> roots;
      for (int i = 0; i < n; ++i) {
        if (!leaf[i] && !branch[i] && mark[i]) {
          roots.emplace_back(i);
        }
      }
      min_size = n, min_cost = 0, ways = 1;
      for (int i = 0; i < n; ++i) {
        if (branch[i]) min_cost += cost[i];
        if (branch[i] || leaf[i]) --min_size;
      }
      int size = 0;
      for (auto &&r: roots) {
        auto t = dfs(r);
        ways = 1ll * ways * t.second % mod;
        size += t.first;
        ways = 1ll * ways * binom[size][t.first] % mod;
        min_cost += cost[r];
      }
    }
    printf("Case #%d: %d %d %d\n", cas, min_size, min_cost, ways);
  }
  return 0;
}

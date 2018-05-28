#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

const int N = 300, F = 11;

using pii = std::pair<int, int>;

std::vector<int> edges[N];
std::pair<int, int> dp[1 << F][N];
int weight[N], vis[N];

pii operator + (const pii& a, const pii& b) {
  return {a.first + b.first, a.second + b.second};
}

pii steiner() {
  int n, f, m;
  scanf("%d%d%d", &n, &f, &m);
  for (int i = 0; i < n; ++i) {
    edges[i].clear();
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u].emplace_back(v);
    edges[v].emplace_back(u);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &weight[i]);
  }
  int s = 1 << f;
  for (int mask = 0; mask < s; ++mask) {
    for (int i = 0; i < n; ++i) {
      dp[mask][i] = {1e9, 0};
    }
  }
  for (int i = 0; i < f; ++i) {
    dp[1 << i][i] = {weight[i], 1};
  }
  for (int mask = 0; mask < s; ++mask) {
    for (int u = 0; u < n; ++ u) for (auto &v: edges[u]) {
      for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
        dp[mask][u] = std::min(dp[mask][u], dp[sub][v] + dp[mask ^ sub][u]);
      }
    }
    std::queue<int> Q;
    for (int u = 0; u < n; ++ u) {
      if (dp[mask][u].first != 1e9) {
        Q.push(u), vis[u] = true;
      }
    }
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      vis[u] = false;
      for (auto &v: edges[u]) {
        if (dp[mask][v] > dp[mask][u] + pii(weight[v], 1)) {
          dp[mask][v] = dp[mask][u] + pii(weight[v], 1);
          if (!vis[v]) Q.emplace(v);
          vis[v] = true;
        }
      }
    }
  }
  pii ret = {1e9, 0};
  for (int i = 0; i < n; ++ i) {
    ret = std::min(ret, dp[s - 1][i]);
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    auto res = steiner();
    printf("Case #%d: %d %d\n", cas, res.first, res.second);
  }
  return 0;
}

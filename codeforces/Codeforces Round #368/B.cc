#include <bits/stdc++.h>
using LL = long long;
using PII = std::pair<int, int>;

const int N = 100000 + 10;

std::vector<PII> G[N];
LL dis[N];
int vis[N];
int n, m, k;

void run() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    G[u].push_back(PII(v, w));
    G[v].push_back(PII(u, w));
  }
  for (int i = 1; i <= n; ++i) {
    dis[i] = 1ll << 60;
    vis[i] = 0;
  }
  std::queue<int> Q;
  for (int i = 0; i < k; ++i) {
    int x;
    scanf("%d", &x);
    Q.push(x);
    dis[x] = 0;
    vis[x] = true;
  }
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    vis[u] = false;
    for (auto &&x: G[u]) {
      int v = x.first, w = x.second;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (!vis[v]) Q.push(v);
        vis[v] = true;
      }
    }
  }
  LL ret = 1ll << 60;
  for (int i = 1; i <= n; ++i) {
    if (dis[i] != 0) ret = std::min(ret, dis[i]);
  }
  if (ret == (1ll << 60)) ret = -1;
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}

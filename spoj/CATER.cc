#include <cstdio>
#include <vector>

const int N = 2500 + 10, K = 100;
const int mod = 10243;

std::vector<int> edges[N];
int dp[N][K], size[N];
int n, k, total, root, mins;
bool mark[N];

void get_center(int u, int p = -1) {
  int mx = 0;
  size[u] = 1;
  for (auto &&v: edges[u]) if (v != p && !mark[v]) {
    get_center(v, u);
    size[u] += size[v];
    mx = std::max(mx, size[v]);
  }
  mx = std::max(mx, total - size[u]);
  if (mx < mins) {
    mins = mx;
    root = u;
  }
}

void dfs(int u, int m, int p = -1) {
  size[u] = 1;
  for (auto &&v: edges[u]) if (v != p && !mark[v]) {
    for (int i = 0; i < m; ++i) dp[v][i] = dp[u][i];
    dfs(v, m - 1, u);
    size[u] += size[v];
    for (int i = 1; i <= m; ++i) {
      dp[u][i] = (dp[u][i] + dp[v][i - 1]) % mod;
    }
  }
}

int solve(int u, int _n) {
  if (_n < k) return 0;
  total = _n;
  mins = _n * 10;
  get_center(u);
  u = root;
  mark[u] = true;
  for (int i = 0; i <= k; ++i) dp[u][i] = 0;
  dp[u][0] = 1;
  dfs(u, k - 1);
  int ret = dp[u][k - 1];
  for (auto &&v: edges[u]) if (!mark[v]) {
    ret += solve(v, size[v]);
  }
  return ret % mod;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].emplace_back(v - 1);
    edges[v - 1].emplace_back(u - 1);
  }
  printf("%d\n", solve(0, n));
  return 0;
}

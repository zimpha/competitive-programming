#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 150000 + 10;
const int inf = 1e9;

std::vector<int> edges[N];
int parent[N], order[N], sz;
int ht[N], dp[N], ret[N];
int n;

void dfs(int u, int p = -1) {
  parent[u] = p;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
  }
  order[sz++] = u;
}

int solve(int d) {
  for (int i = 0; i < n; ++i) ht[i] = 0;
  for (int i = 0; i < n; ++i) dp[i] = inf;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int v = order[i], u = parent[v];
    if (ht[v] + dp[v] <= d) ht[v] = -inf;
    if (ht[v] >= d || (v == 0 && ht[v] >= 0)) {
      ++ret;
      dp[v] = 0;
      ht[v] = -inf;
    }
    dp[u] = std::min(dp[u], dp[v] + 1);
    ht[u] = std::max(ht[u], ht[v] + 1);
  }
  return ret;
}

void divide(int l, int r, int ll, int rr) {
  if (l > r) return;
  if (ll == rr) {
    for (int i = l; i <= r; ++i) ret[i] = ll;
    return;
  }
  int m = (l + r) >> 1;
  ret[m] = solve(m);
  divide(l, m - 1, ret[m], rr);
  divide(m + 1, r, ll, ret[m]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(0);
  int sq = sqrt(n * 2);
  for (int d = 1; d <= sq; ++d) {
    ret[d] = solve(d);
  }
  divide(sq, n, 1, ret[sq]);
  ret[0] = n;
  for (int k = 1, d = n; k <= n; ++k) {
    while (d >= 1 && ret[d - 1] <= k) --d;
    printf("%d ", d);
  }
  puts("");
  return 0;
}

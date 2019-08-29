#include <cstdio>
#include <cstring>
#include <vector>

const int N = 3001;

std::vector<int> edges[N];
short dp[N][N];
int size[N], best[N];
int n;

void dfs(int u, int p = -1) {
  size[u] = 1;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    size[u] += size[v];
  }
  static int f[N], g[N];
  memset(f, 0, sizeof(f));
  int s = 0;
  for (auto &v: edges[u]) if (v != p) {
    for (int i = 0; i <= s + size[v]; ++i) g[i] = -1;
    for (int i = 0; i <= size[v]; ++i) {
      int w = i == 0 ? 1 : dp[v][i];
      for (int j = 0; j <= s; ++j) {
        if (g[i + j] == -1 || g[i + j] > f[j] + w) {
          g[i + j] = f[j] + w;
        }
      }
    }
    s += size[v];
    for (int i = 0; i <= s; ++i) f[i] = g[i];
  }
  for (int i = 0; i <= s; ++i) dp[u][i + 1] = f[i];
  int extra = p != -1;
  for (int i = 1; i <= size[u]; ++i) if (dp[u][i] != -1) {
    if (best[i] == -1 || best[i] > dp[u][i] + extra) {
      best[i] = dp[u][i] + extra;
    }
  }
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
  for (int i = 1; i <= n; ++i) best[i] = -1;
  dfs(0);
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    printf("%d\n", best[x]);
  }
  return 0;
}

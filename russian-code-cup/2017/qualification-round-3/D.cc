#include <cstdio>
#include <vector>
#include <cstring>

const int N = 100000 + 10, K = 30;
const int mod = 1e9 + 7;

std::vector<int> edges[N];
int f[N][K], g[N][K], w[N];
int n, k;

void dfs(int u, int d, int s[]) {
  int p = 1;
  for (int i = 0; i <= k; ++i) {
    s[i] = (s[i] + g[u][i]) % mod;
    w[u] = (w[u] + 1ll * p * s[i]) % mod;
    p = 1ll * p * d % mod;
  }
  for (auto &&v: edges[u]) {
    dfs(v, d + 1, s);
    for (int i = 0; i <= k; ++i) {
      f[u][i] = (f[u][i] + f[v][i]) % mod;
    }
  }
  p = 1;
  for (int i = 0; i <= k; ++i) {
    s[i] = (s[i] - g[u][i] + mod) % mod;
    w[u] = (w[u] + 1ll * p * f[u][i]) % mod;
    p = 1ll * p * d % mod;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &k);
    int rt;
    for (int i = 0; i < n; ++i) {
      edges[i].clear();
      w[i] = 0;
      for (int j = 0; j <= k; ++j) {
        f[i][j] = g[i][j] = 0;
      }
    }
    for (int i = 0; i < n; ++i) {
      int p;
      scanf("%d", &p);
      if (p) edges[p - 1].push_back(i);
      else rt = i;
    }
    int q;
    scanf("%d", &q);
    for (int it = 0; it < q; ++it) {
      int t, v, p, ret = 0;
      scanf("%d%d", &t, &v);
      for (int i = 0; i <= k; ++i) {
        scanf("%d", &p);
        if (t == 1) g[v - 1][i] = (g[v - 1][i] + p) % mod;
        else f[v - 1][i] = (f[v - 1][i] + p) % mod;
      }
    }
    int s[K];
    memset(s, 0, sizeof(s));
    dfs(rt, 1, s);
    for (int i = 0; i < n; ++i) {
      printf("%d ", w[i]);
    }
    puts("");
  }
  return 0;
}

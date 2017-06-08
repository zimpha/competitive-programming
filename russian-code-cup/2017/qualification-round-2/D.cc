#include <cstdio>

const int N = 500000 + 10, M = 30;
const int mod = 1e9 + 7;

int l[N], r[N];
int f[N][M], g[N][M];
int n;

void dfs(int u) {
  if (l[u] != -1) dfs(l[u]);
  if (r[u] != -1) dfs(r[u]);
  for (int h = 0; h < M; ++h) {
    // f[u][h] = \prod (g[][h - 1] + f[][h - 1])
    // g[u][h] = \prod f[][h]
    if (h > 0) {
      int x = l[u] == -1 ? h == 1 : (f[l[u]][h - 1] + g[l[u]][h - 1]);
      int y = r[u] == -1 ? h == 1 : (f[r[u]][h - 1] + g[r[u]][h - 1]);
      f[u][h] = 1ll * x * y % mod;
    }
    int x = l[u] == -1 ? h == 0 : f[l[u]][h];
    int y = r[u] == -1 ? h == 0 : f[r[u]][h];
    g[u][h] = 1ll * x * y % mod;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", l + i, r + i);
    --l[i], --r[i];
  }
  dfs(0);
  int ret = 0;
  for (int i = 0; i < M; ++i) {
    ret = (ret + f[0][i]) % mod;
  }
  printf("%d\n", ret);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>

const int mod = 1e9 + 7;
const int M = 302;

int f[2][M], g[2][M];

void upd(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  freopen("sequence.in", "r", stdin);
  freopen("sequence.out", "w", stdout);
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  f[0][a[0]] = 1;
  for (int i = 1; i < n; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(f[u], 0, sizeof(f[u]));
    memset(g[u], 0, sizeof(g[u]));
    for (int j = 0; j <= a[i]; ++j) {
      upd(f[u][j], f[v][a[i] - j]);
      upd(f[u][j], g[v][a[i] - j]);
    }
    for (int j = M - 2; j >= 0; --j) {
      upd(f[v][j], f[v][j + 1]);
    }
    for (int j = 0; j <= a[i]; ++j) {
      g[u][j] = f[v][a[i] - j + 1];
    }
  }
  int ret = g[(n - 1) & 1][0];
  for (int i = 0; i < M; ++i) {
    upd(ret, f[(n - 1) & 1][i]);
  }
  printf("%d\n", ret);
  return 0;
}

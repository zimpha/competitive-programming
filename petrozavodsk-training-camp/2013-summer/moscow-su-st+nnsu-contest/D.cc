#include <cstdio>
#include <vector>

using i64 = long long;

const int N = 50000 + 10;

std::vector<int> edges[N];
int cnt[N][51][50];
i64 vs[N][51];
int col[N], parent[N];

void dfs(int u, int p = -1) {
  parent[u] = p;
  for (auto &v: edges[u]) {
    if (v != p) dfs(v, u);
  }
}

int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  int n, k, q;
  scanf("%d%d%*d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &col[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(0);
  for (int v = 0; v < n; ++v) {
    int c = col[v];
    for (int u = v, i = 0; i <= k && u != -1; ++i) {
      if (++cnt[u][i][c] == 1) {
        vs[u][i] ^= i64(1) << c;
      }
      u = parent[u];
    }
  }
  scanf("%d", &q);
  for (int it = 0; it < q; ++it) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    --x;
    if (op == 1) {
      int &c = col[x];
      for (int u = x, i = 0; i <= k && u != -1; ++i) {
        if (--cnt[u][i][c] == 0) {
          vs[u][i] ^= i64(1) << c;
        }
        u = parent[u];
      }
      c = y;
      for (int u = x, i = 0; i <= k && u != -1; ++i) {
        if (++cnt[u][i][c] == 1) {
          vs[u][i] ^= i64(1) << c;
        }
        u = parent[u];
      }
    } else {
      i64 ret = 0;
      for (int i = 0, u = x; i <= y && u != -1; ++i) {
        for (int j = 0; i + j <= y; ++j) {
          ret |= vs[u][j];
        }
        u = parent[u];
      }
      printf("%d\n", __builtin_popcountll(ret));
    }
  }
  return 0;
}

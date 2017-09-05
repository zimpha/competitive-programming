#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

namespace Tree {
  using int64 = long long;

  const int N = 100000 + 10, K = 17, M = 1e9 + 7;
  std::vector<int> G[N];
  int dep[N], f[N][K + 1];
  int st[N], ed[N], loc[N << 1];
  int n, m, P, dfn;
  void dfs(int x, int par = -1) {
    loc[st[x] = dfn++] = x;
    for (int i = 1; i <= K; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
    for (auto &y: G[x]) if (y != par) {
      dep[y] = dep[f[y][0] = x] + 1;
      dfs(y, x);
    }
    loc[ed[x] = dfn++] = x;
  }
  int lca(int x, int y) {
    if (x == y) return x;
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = K; ~i; --i) {
      if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = K; ~i; --i) {
      if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
  }

  int val[N], type[N], vis[N];
  int64 cnt[N][2], sum;
  void deal(int x) {//这部分维护序列
    int c = val[x], t = type[x];
    vis[x] ^= 1;
    sum -= cnt[c][0] * cnt[c][1];
    if (!vis[x]) cnt[c][t]--;
    else cnt[c][t]++;
    sum += cnt[c][0] * cnt[c][1];
  }
  struct Node {
    int l, r, z, id;
    bool operator < (const Node &rhs) {
      return l / P == rhs.l / P ? r < rhs.r : l / P < rhs.l / P;
    }
  } Q[N];
  int64 ans[N];
  void run() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", type + i);
    for (int i = 1; i <= n; ++i) scanf("%d", val + i);
    std::vector<int> xs(val + 1, val + 1 + n);
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    for (int i = 1; i <= n; ++i) {
      val[i] = std::lower_bound(xs.begin(), xs.end(), val[i]) - xs.begin();
    }
    for (int i = 1; i < n; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    dfs(dep[1] = 1);
    P = sqrt(n * 2);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
      int x, y; scanf("%d%d", &x, &y);
      if (st[x] > st[y]) std::swap(x, y);
      int z = lca(x, y); Q[i].id = i;
      if (z == x) Q[i].l = st[x], Q[i].r = st[y];
      else Q[i].l = ed[x], Q[i].r = st[y], Q[i].z = z;
    }
    std::sort(Q, Q + m);
    for (int i = 0, l = 0, r = -1; i < m; ++i) {
      if (r < Q[i].r) {
        for (++r; r <= Q[i].r; ++r) deal(loc[r]);
        --r;
      }
      for (; r > Q[i].r; --r) deal(loc[r]);
      for (; l < Q[i].l; ++l) deal(loc[l]);
      if (l > Q[i].l) {
        for (--l; l >= Q[i].l; --l) deal(loc[l]);
        ++l;
      }
      if (Q[i].z) deal(Q[i].z);
      //printf("%lld\n", sum);
      ans[Q[i].id] = sum;
      if (Q[i].z) deal(Q[i].z);
    }
    for (int i = 0; i < m; ++ i) printf("%lld\n", ans[i]);
  }
}

int main() {
  Tree::run();
  return 0;
}
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>

using int64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 10;
constexpr int M = 1e5 + 10;
constexpr int K = 16;

struct query_t {
  int l, r, t, z;
} ask[N];

std::vector<int> query[60][60];
std::vector<int> edges[N];
int dfn[N * 2], st[N], ed[N], sz;
int pos[N * 2], a[N], value[N];
int fa[N][K + 1], dep[N];
int n, q, B;

void dfs(int u, int p) {
  dfn[st[u] = ++sz] = u;
  fa[u][0] = p;
  for (int i = 1; i < K; ++i) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  }
  for (auto &&v: edges[u]) if (v != p) {
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
  dfn[ed[u] = ++sz] = u;
}

int lca(int x, int y) {
  if (x == y) return x;
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = K; ~i; --i) {
    if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
  }
  if (x == y) return x;
  for (int i = K; ~i; --i) {
    if (fa[x][i] == fa[y][i]) continue;
    x = fa[x][i], y = fa[y][i];
  }
  return fa[x][0];
}

namespace mo {
  int cnt[M], mark[N];
  int64 ret;
  void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(mark, 0, sizeof(mark));
    ret = 0;
  }
  void add(int x) {
    int v = value[x];
    if (mark[x]) ret -= --cnt[v];
    else ret += cnt[v]++;
    mark[x] ^= 1;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u].emplace_back(v);
    edges[v].emplace_back(u);
  }
  sz = 0;
  dep[0] = 0;
  dfs(0, 0);

  for (B = 1; B * B * B < sz; ++B);
  B = B * B;
  std::vector<pii> modify;
  for (int i = 0; i < q; ++i) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      ask[i].t = -2;
      modify.emplace_back(x, y);
    } else {
      if (st[x] > st[y]) std::swap(x, y);
      int z = lca(x, y);
      int l = (z == x) ? st[x] : ed[x];
      int r = st[y];
      ask[i].t = modify.size() - 1;
      ask[i].z = (z == x) ? -1 : z;
      ask[i].l = l;
      ask[i].r = r;
      query[l / B][r / B].emplace_back(i);
    }
  }
  std::vector<int64> ret(q);
  int m = (sz - 1) / B + 1;
  for (int i = 0; i < m; ++i) {
    for (int j = i; j < m; ++j) {
      if (query[i][j].empty()) continue;
      memcpy(value, a, sizeof(*a) * n);
      mo::init();
      int t = 0, l = 0, r = -1;
      for (auto &&v: query[i][j]) {
        auto qr = ask[v];
        if (r < qr.r) {
          for (++r; r <= qr.r; ++r) mo::add(dfn[r]);
          --r;
        }
        while (r > qr.r) mo::add(dfn[r--]);
        while (l < qr.l) mo::add(dfn[l++]);
        if (l > qr.l) {
          for (--l; l >= qr.l; --l) mo::add(dfn[l]);
          ++l;
        }
        for (int x, y; t <= qr.t; ++t) {
          std::tie(x, y) = modify[t];
          bool flag = (qr.l <= st[x] && st[x] <= qr.r) ^ (qr.l <= ed[x] && ed[x] <= qr.r);
          if (flag) mo::add(x);
          value[x] = y;
          if (flag) mo::add(x);
        }
        if (qr.z != -1) mo::add(qr.z);
        ret[v] = mo::ret;
        if (qr.z != -1) mo::add(qr.z);
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    if (ask[i].t == -2) continue;
    printf("%lld\n", ret[i]);
  }
  return 0;
}

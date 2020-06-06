#include <cstdio>
#include <vector>

using int64 = long long;

const int N = 5e5 + 10;
const int mod = 1e9 + 7;

std::vector<std::pair<int, int>> down[N];
std::vector<int> edges[N];
int depth[N], c[N], size[N];
int fa[N][20], n, q;

void dfs(int u, int p = 0) {
  fa[u][0] = p;
  for (int i = 1; i < 20; ++i) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  }
  for (auto &v: edges[u]) if (v != p) {
    depth[v] = depth[u] + 1;
    size[u]++;
    dfs(v, u);
  }
}

int up(int u, int d) {
  for (int i = 0; d; d >>= 1, ++i) {
    if (d & 1) u = fa[u][i];
  }
  return u;
}

int64 ret[N], inv[N];

struct Node {
  int64 val, tag;
  void apply(int64 w) {
    tag = tag * w % mod;
    val = val * w % mod;
  }
} T[N << 1];

void push(int o) {
  if (T[o].tag != 1) {
    T[o << 1].apply(T[o].tag);
    T[o << 1 | 1].apply(T[o].tag);
    T[o].tag = 1;
  }
}

void build(int o, int l, int r) {
  T[o].val = 0; T[o].tag = 1;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

int64 add(int o, int l, int r, int x, int64 v) {
  if (l + 1 == r) return T[o].val = (T[o].val + v) % mod;
  push(o);
  int m = (l + r) >> 1;
  if (x < m) return add(o << 1, l, m, x, v);
  else return add(o << 1 | 1, m, r, x, v);
}

void mul(int o, int l, int r, int L, int R, int64 v) {
  if (L <= l && R >= r) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) mul(o << 1, l, m, L, R, v);
  if (R > m) mul(o << 1 | 1, m, r, L, R, v);
}

void solve(int u, int p = 0) {
  for (auto &e: down[u]) {
    int t = e.second + depth[u];
    if (t < n) add(1, 0, n, t, e.first);
  }
  ret[u] = add(1, 0, n, depth[u], 0);
  if (size[u]) mul(1, 0, n, depth[u] + 1, n, inv[size[u]]);
  for (auto &v: edges[u]) if (v != p) {
    solve(v, u);
  }
  if (size[u]) mul(1, 0, n, depth[u] + 1, n, size[u]);
  for (auto &e: down[u]) {
    int t = e.second + depth[u];
    if (t < n) add(1, 0, n, t, mod - e.first);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i]);
  }
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(1);
  scanf("%d", &q);
  std::vector<char> qt(q);
  std::vector<int> qv(q), qx(q); 
  for (int i = 0; i < q; ++i) {
    static char op[10];
    scanf("%s", op);
    qt[i] = op[0];
    if (op[0] == '+') scanf("%d%d", &qv[i], &qx[i]);
  }
  int c_up = 0, c_down = 0;
  for (int i = q - 1; i >= 0; --i) {
    if (qt[i] == '+') {
      int d = std::min(depth[qv[i]], c_up);
      int u = up(qv[i], d);
      down[u].emplace_back(qx[i], c_down);
    } else if (qt[i] == '^') {
      c_up++;
    } else {
      if (c_up) --c_up;
      else ++c_down;
    }
  }
  for (int i = 1; i <= n; ++i) {
    int d = std::min(depth[i], c_up);
    int u = up(i, d);
    down[u].emplace_back(c[i], c_down);
  }

  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
  solve(1);
  for (int i = 1; i <= n; ++i) printf("%lld ", ret[i]);
  puts("");
  return 0;
}

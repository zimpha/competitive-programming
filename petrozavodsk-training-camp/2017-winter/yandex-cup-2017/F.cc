#include <cstdio>
#include <vector>

const int N = 5000 + 10, mod = 1e9 + 7;

std::vector<int> tree[N];
int fac[N], inv[N];
int parent[N], NoS[N];
int sz[N];

void add_mod(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

int pow_mod(int a, int n) {
  int r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = 1ll * r * a % mod;
    a = 1ll * a * a % mod;
  }
  return r;
}

void prepare() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[i] = pow_mod(fac[i], mod - 2);
  }
}

int choose(int n, int m) {
  return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod;
}

void dfs(int u) {
  sz[u] = 0;
  NoS[u] = 1;
  for (auto &&v: tree[u]) {
    dfs(v);
    NoS[u] = 1ll * NoS[u] * NoS[v] % mod;
    sz[u] += sz[v];
    NoS[u] = 1ll * NoS[u] * choose(sz[u], sz[v]) % mod;
  }
  ++sz[u];
}

int main() {
  prepare();
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d", parent + i);
    tree[--parent[i]].push_back(i);
  }
  dfs(0);
  int v, k;
  scanf("%d%d", &v, &k);
  std::vector<int> f(n + 1, 0);
  f[1] = NoS[--v];
  for (; v != 0; v = parent[v]) {
    int p = parent[v], coef = 1;
    int now = 0;
    for (auto &&u: tree[p]) {
      if (u == v) continue;
      now += sz[u];
      coef = 1ll * coef * choose(now, sz[u]) % mod;
      coef = 1ll * coef * NoS[u] % mod;
    }
    std::vector<int> g(n + 1, 0);
    for (int i = 1; i <= sz[v]; ++i) {
      if (!f[i]) continue;
      for (int j = 0; j < sz[p] - sz[v]; ++j) {
        add_mod(g[i + j + 1], 1ll * choose(i - 1 + j, j) * choose(sz[v] - i + sz[p] - sz[v] - j - 1, sz[v] - i) % mod * f[i] % mod);
      }
    }
    for (auto &&v: g) {
      v = 1ll * v * coef % mod;
    }
    f.swap(g);
  }
  printf("%d\n", f[k]);
  return 0;
}

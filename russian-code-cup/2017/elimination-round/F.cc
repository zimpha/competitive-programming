#include <bits/stdc++.h>

using ull = unsigned long long;

const int N = 100000 + 10, seed = 1e9 + 7;
std::vector<int> G[N], stack;
ull hash[N];
int eq[20][N];
int ht[N];
int n;

void dfs(int u) {
  ht[u] = 0;
  for (auto &&v: G[u]) {
    dfs(v);
    ht[u] = std::max(ht[v] + 1, ht[u]);
  }
}

void dfs(int u, int k, int c[]) {
  if (k <= stack.size()) {
    int x = k ? stack[stack.size() - k] : u;
    hash[x] = hash[x] * seed + c[u] + 1;
  }
  stack.push_back(u);
  for (auto &&v: G[u]) dfs(v, k, c);
  stack.pop_back();
}

void merge(int la, int lb, int a[], int b[], int c[]) {
  for (int i = 0; i < n; ++i) {
    hash[i] = a[i] + 1;
  }
  stack.clear();
  dfs(0, la, b);
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return hash[x] < hash[y];
  });
  int m = 0;
  for (int i = 0; i < n; ++i) {
    if (!i || hash[id[i]] != hash[id[i - 1]]) ++m;
    c[id[i]] = m - 1;
  }
}

bool check(int c[], int level) {
  static int cnt[N];
  memset(cnt, 0, sizeof(*cnt) * n);
  for (int i = 0; i < n; ++i) {
    if (ht[i] >= level) cnt[c[i]]++;
  }
  for (int i = 0; i < n; ++i) {
    if (cnt[i] > 1) return true;
  }
  return false;
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    G[i].clear();
    int m; scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int x;
      scanf("%d", &x);
      G[i].push_back(x - 1);
    }
    eq[0][i] = m;
  }
  dfs(0);
  int m = 0;
  for (int i = 1; (1 << i) <= ht[0]; ++i) {
    merge(1 << (i - 1), 1 << (i - 1), eq[i - 1], eq[i - 1], eq[i]);
    m = i;
  }
  static int hash[N], tmp[N];
  memset(hash, 0, sizeof(*hash) * n);
  int level = 0;
  for (int i = m; i >= 0; --i) {
    merge(level, 1 << i, hash, eq[i], tmp);
    if (check(tmp, level + (1 << i))) {
      memcpy(hash, tmp, sizeof(*tmp) * n);
      level += 1 << i;
    }
  }
  printf("%d\n", level);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    solve();
  }
  return 0;
}

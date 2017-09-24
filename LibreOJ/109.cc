#include <cstdio>
#include <algorithm>

const int N = 4e6 + 10, mod = 998244353;

int dsu[N], rank[N];

int root(int x) {
  if (dsu[x]) dsu[x] = root(dsu[x]);
  return dsu[x];
}

void merge(int u, int v) {
  u = root(u), v = root(v);
  if (u == v) return;
  if (rank[u] < rank[v]) dsu[u] = v;
  else {
    dsu[v] = u;
    if (rank[u] == rank[v]) ++rank[u];
  }
}

inline int ask(int u, int v) {
  return root(u) == root(v);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    dsu[i] = -1;
  }
  int ret = 0;
  for (int i = 0; i < m; ++i) {
    int op, u, v;
    scanf("%d%d%d", &op, &u, &v);
    if (op == 0) merge(u, v);
    else ret = (ret * 2 + ask(u, v)) % mod;
  }
  printf("%d\n", ret);
  return 0;
}

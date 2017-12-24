#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 4e5, mod = 1e9 + 7;

std::vector<int> edges[N], ql[N];
int weight[N], xs[N], m;
int st[N], ed[N], n, sz;
int nx[N], pos[N], s[N];

void dfs(int u) {
  s[sz] = u;
  st[u] = sz++;
  for (auto &&v: edges[u]) dfs(v);
  ed[u] = sz;
}

int bit[N];
void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) bit[x] += v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, p; i < n; ++i) {
    scanf("%d", &p);
    edges[p].emplace_back(i);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &weight[i]);
    xs[i] = weight[i];
  }
  std::sort(xs, xs + n);
  m = std::unique(xs, xs + n) - xs;
  dfs(0);
  for (int i = 0; i < m; ++i) pos[i] = -1;
  for (int i = n - 1; i >= 0; --i) {
    int w = std::lower_bound(xs, xs + m, weight[s[i]]) - xs;
    nx[i] = pos[w];
    pos[w] = i;
  }
  for (int i = 0; i < n; ++i) {
    ql[st[i]].emplace_back(i);
  }
  int64 ret = 1;
  for (int i = n - 1; i >= 0; --i) {
    add(i, 1);
    if (nx[i] != -1) add(nx[i], -1);
    for (auto &&x: ql[i]) {
      ret *= get(ed[x] - 1);
      ret %= mod;
    }
  }
  printf("%lld\n", ret);
  return 0;
}

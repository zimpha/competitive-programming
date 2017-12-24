#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 100000 + 10, mod = 1e9 + 7;

std::vector<std::pair<int, int>> edges[N];
int size[N], dep[N], n;

void dfs1(int u, int p = -1) {
  size[u] = 1;
  for (auto &&e: edges[u]) if (e.first != p) {
    int v = e.first;
    dep[v] = dep[u] + 1;
    dfs1(v, u);
    size[u] += size[v];
  }
}

int64 dfs2(int u, int64 s, int p = -1) {
  int64 ret = 0;
  for (auto &&e: edges[u]) if (e.first != p) {
    int v = e.first;
    ret += dfs2(v, s + size[u], u);
    ret -= dep[v] * size[v] % mod * size[v] % mod * e.second % mod;
    ret += (s + size[u]) % mod * size[v] % mod * e.second % mod;
  }
  ret %= mod; ret += mod; ret %= mod;
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      --u, --v;
      edges[u].emplace_back(v, w);
      edges[v].emplace_back(u, w);
    }
    dfs1(0);
    auto ret = dfs2(0, 0);
    printf("Case %d: %lld\n", cas, ret);
  }
  return 0;
}

#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 2e5 + 10;

std::vector<int> edges[N];
std::vector<int> f[N];
std::vector<i64> g[N];
int ht[N], offset_g[N];
i64 buffer[N];

i64 dfs(int u, int p = -1) {
  i64 ret = 0;
  ht[u] = 0;
  int mv = -1, smv = -1;
  for (auto &v: edges[u]) if (v != p) {
    ret += dfs(v, u);
    ht[u] = std::max(ht[u], ht[v] + 1);
    if (smv == -1 || f[v].size() > f[smv].size()) smv = v;
    if (mv == -1 || f[smv].size() > f[mv].size()) std::swap(mv, smv);
  }
  if (mv != -1) {
    f[u].swap(f[mv]), g[u].swap(g[mv]);
    offset_g[u] = offset_g[mv];
  } else {
    offset_g[u] = -1;
    g[u] = {};
    f[u] = {};
  }
  int bound = smv != -1 ? ht[smv] : 0;
  memset(buffer, 0, sizeof(*buffer) * (bound + 1));
  for (auto &v: edges[u]) {
    if (v == p || v == mv) continue;
    for (int d = 2; d < (int)g[v].size() - offset_g[v]; ++d) {
      ret += f[u][ht[mv] - (d - 2)] * g[v][offset_g[v] + d];
    }
    for (int d = 0; d <= ht[v]; ++d) {
      i64 wd = f[v][ht[v] - d];
      ret += wd * buffer[d];
      if (offset_g[u] + d + 2 < (int)g[u].size()) {
        ret += wd * g[u][d + 2 + offset_g[u]];
      }
      buffer[d] += wd * f[u][ht[mv] - d];
      f[u][ht[mv] - d] += wd;
      g[u].at(offset_g[u] + d) += g[v].at(offset_g[v] + d);
    }
  }
  offset_g[u]++;
  for (int i = 0; i <= bound; ++i) {
    while ((int)g[u].size() <= offset_g[u] + i + 1) g[u].push_back(0);
    g[u].at(offset_g[u] + i + 1) += buffer[i];
  }
  f[u].push_back(1);
  while (offset_g[u] + ht[u] >= (int)g[u].size()) g[u].push_back(0);
  ret += g[u][offset_g[u]];
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u - 1].push_back(v - 1);
      edges[v - 1].push_back(u - 1);
    }
    i64 ret = dfs(0);
    printf("%lld\n", ret);
  }
  return 0;
}

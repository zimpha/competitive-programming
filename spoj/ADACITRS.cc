#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 3e5 + 10, S = N * 3;

uint64 seed[S];

std::map<uint64, int> cache;

int get_id(uint64 v) {
  int id = cache.size();
  if (cache.count(v)) id = cache[v];
  else cache[v] = id;
  return id;
}

uint64 hs1[N], hv1[N];
uint64 hs2[N], hv2[N];
std::vector<int> edges[N];

void dfs1(int u, int p = -1) {
  hv1[u] = seed[0];
  for (auto &&v: edges[u]) if (v != p) {
    dfs1(v, u);
    hv1[u] += seed[hs1[v]];
  }
  hs1[u] = get_id(hv1[u]);
}

void dfs2(int u, int p = -1) {
  for (auto &&v: edges[u]) if (v != p) {
    uint64 tmp = get_id(hv2[u] - seed[hs1[v]]);
    hv2[v] = hv1[v] + seed[tmp];
    hs2[v] = get_id(hv2[v]);
    dfs2(v, u);
  }
}

int main() {
  for (int i = 0; i < S; ++i) {
    seed[i] = (uint64)rand() << 48 | (uint64)rand() << 32 | (uint64)rand() << 16 | (uint64)rand();
  }
  int n;
  scanf("%d", &n);
  std::vector<int> degree(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u].emplace_back(v);
    edges[v].emplace_back(u);
    degree[u]++;
    degree[v]++;
  }
  dfs1(0);
  hs2[0] = hs1[0];
  hv2[0] = hv1[0];
  dfs2(0);
  std::vector<uint64> candidate;
  for (int i = 0; i < n; ++i) {
    if (degree[i] > 1) continue;
    candidate.emplace_back(hs2[i]);
  }
  std::sort(candidate.begin(), candidate.end());
  int ret = std::unique(candidate.begin(), candidate.end()) - candidate.begin();
  printf("%d\n", ret);
  return 0;
}

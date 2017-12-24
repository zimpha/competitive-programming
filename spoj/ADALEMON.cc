#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 3e5 + 10;

uint64 seed[N];

std::map<uint64, int> cache;

int get_id(uint64 v) {
  int id = cache.size();
  if (cache.count(v)) id = cache[v];
  else cache[v] = id;
  return id;
}

uint64 hash[N];
std::vector<int> edges[N];

void get_hash(int u, int p = -1) {
  uint64 hv = seed[0];
  for (auto &&v: edges[u]) if (v != p) {
    get_hash(v, u);
    hv += seed[hash[v]];
  }
  hash[u] = get_id(hv);
}

int main() {
  for (int i = 0; i < N; ++i) {
    seed[i] = (uint64)rand() << 48 | (uint64)rand() << 32 | (uint64)rand() << 16 | (uint64)rand();
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      edges[i].clear();
    }
    std::vector<int> degree(n);
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u].emplace_back(v);
      edges[v].emplace_back(u);
      degree[u]++;
      degree[v]++;
    }
    std::vector<uint64> candidate;
    for (int i = 0; i < n; ++i) {
      if (degree[i] != 1) continue;
      get_hash(i);
      candidate.emplace_back(hash[i]);
    }
    if (n == 1) puts("1");
    else {
      std::sort(candidate.begin(), candidate.end());
      int ret = std::unique(candidate.begin(), candidate.end()) - candidate.begin();
      printf("%d\n", ret);
    }
  }
  return 0;
}

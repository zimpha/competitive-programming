#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using uint64 = unsigned long long;
using int64 = long long;

template<class T = uint64, int B = 64>
struct XorBasis {
  T base[B];
  void init() { memset(base, 0, sizeof(base)); }
  void add(T x) {
    for (int i = B - 1; i >= 0; --i) if (x >> i & 1) {
      if (base[i]) x ^= base[i];
      else { base[i] = x; return; }
    }
  }
  bool check(T x) const {
    for (int i = B - 1; i >= 0; --i) if (x >> i & 1) {
      if (base[i]) x ^= base[i];
      else return true;
    }
    return false;
  }
  T query_max(T x) const {
    for (int i = B - 1; i >= 0; --i) {
      if (base[i] && (~x >> i & 1)) x ^= base[i];
    }
    return x;
  }
  void eliminate() {
    for (int i = 0; i < B; ++i) if (base[i]) {
      for (int j = i + 1; j < B; ++j) {
        if (base[j] >> i & 1) base[j] ^= base[i];
      }
    }
  }
  // We should call eliminate() first.
  T query_kth(uint64 k, int n) const {
    int cnt = 0;
    for (int i = 0; i < B; ++i) cnt += base[i] != 0;
    if (cnt != n) --k;
    if (k + 1 > T(1) << cnt) return -1;
    T ret = 0;
    for (int i = 0, j = 0; i < B; ++i) if (base[i]) {
      if (k >> j & 1) ret ^= base[i];
      ++j;
    }
    return ret;
  }
};

const int N = 5e4 + 10, M = 1e5 + 10;

std::vector<int> edges[N];
int S[M], T[M];
uint64 D[M], sum[M];
bool mark[N];

void dfs(int u) {
  mark[u] = true;
  for (auto &e: edges[u]) {
    int v = S[e] + T[e] - u;
    if (!mark[v]) {
      sum[v] = sum[u] ^ D[e];
      dfs(v);
    }
  }
}

int main() {
  XorBasis<> base;
  base.init();
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%llu", &S[i], &T[i], &D[i]);
    --S[i], --T[i];
    edges[S[i]].push_back(i);
    edges[T[i]].push_back(i);
  }
  dfs(0);
  for (int i = 0; i < m; ++i) {
    uint64 x = sum[S[i]] ^ sum[T[i]] ^ D[i];
    base.add(x);
  }
  printf("%llu\n", base.query_max(sum[n - 1]));
  return 0;
}

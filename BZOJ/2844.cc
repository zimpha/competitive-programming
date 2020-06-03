#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int mod = 10086;

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
  int size() const {
    int ret = 0;
    for (int i = 0; i < B; ++i) ret += base[i] != 0;
    return ret;
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
    if (size() != n) --k;
    if (k + 1 > T(1) << size()) return -1;
    T ret = 0;
    for (int i = 0, j = 0; i < B; ++i) if (base[i]) {
      if (k >> j & 1) ret ^= base[i];
      ++j;
    }
    return ret;
  }
  // We should call eliminate() first.
  uint64 rank(T x) const {
    uint64 ret = 0;
    for (int i = 0, j = 0; i < B; ++i) if (base[i]) {
      if (x >> i & 1) ret |= uint64(1) << j;
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
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    uint64 x;
    scanf("%llu", &x);
    base.add(x);
  }
  base.eliminate();
  uint64 q;
  scanf("%llu", &q);
  int size = base.size();
  uint64 rank = base.rank(q);
  int ret = 1;
  for (int i = size; i < n; ++i) {
    ret = ret * 2 % mod;
  }
  ret = rank % mod * ret;
  ret = (ret + 1) % mod;
  printf("%d\n", ret);
  return 0;
}

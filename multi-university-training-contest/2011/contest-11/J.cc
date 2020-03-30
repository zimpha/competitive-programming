#include <cstdio>
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

int main() {
  int T;
  scanf("%d", &T);
  XorBasis<> base;
  for (int cas = 1; cas <= T; ++cas) {
    int n, q;
    scanf("%d", &n);
    base.init();
    for (int i = 0; i < n; ++i) {
      uint64 x;
      scanf("%llu", &x);
      base.add(x);
    }
    base.eliminate();
    scanf("%d", &q);
    printf("Case #%d:\n", cas);
    for (int i = 0; i < q; ++i) {
      uint64 k;
      scanf("%llu", &k);
      int64 ret = base.query_kth(k, n);
      printf("%lld\n", ret);
    }
  }
  return 0;
}

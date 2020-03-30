#include <cstdio>
#include <cstring>
#include <algorithm>

using uint64 = unsigned long long;

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
  T query_max(T x) {
    for (int i = B - 1; i >= 0; --i) {
      if (base[i] && (~x >> i & 1)) x ^= base[i];
    }
    return x;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  XorBasis<> base;
  base.init();
  for (int i = 0; i < n; ++i) {
    uint64 x;
    scanf("%llu", &x);
    base.add(x);
  }
  printf("%llu\n", base.query_max(0));
  return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;

template<class T = u64, int B = 64>
struct XorBasis {
  T base[B];
  void init() { memset(base, 0, sizeof(base)); }
  void add(T x) {
    for (int i = B - 1; i >= 0; --i) if (x >> i & 1) {
      if (base[i]) x ^= base[i];
      else { base[i] = x; return; }
    }
  }
  bool check(T x, int bound) const {
    for (int i = B - 1; i >= bound; --i) if (x >> i & 1) {
      if (base[i]) x ^= base[i];
      else return false;
    }
    return true;
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
  T query_kth(u64 k, int n) const {
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
  u64 rank(T x) const {
    u64 ret = 0;
    for (int i = 0, j = 0; i < B; ++i) if (base[i]) {
      if (x >> i & 1) ret |= u64(1) << j;
      ++j;
    }
    return ret;
  }
};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    XorBasis<i64, 61> base;
    base.init();
    std::vector<i64> a(n);
    i64 sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      sum ^= a[i];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= 60; ++j) {
        if (~a[i] >> j & 1) continue;
        if (~sum >> j & 1) a[i] ^= i64(1) << j;
      }
      base.add(a[i]);
    }
    base.eliminate();
    std::vector<int> bits;
    for (int i = 60; i >= 0; --i) {
      if (sum >> i & 1) bits.push_back(i);
    }
    if (bits.empty()) {
      puts("0");
      continue;
    }
    i64 cur = i64(1) << bits[0];
    for (auto &b: bits) {
      if (b == bits[0]) continue;
      if (base.check(cur, b)) continue;
      cur ^= i64(1) << b;
    }
    printf("%lld\n", std::abs((sum ^ cur) - cur));
  }
  return 0;
}

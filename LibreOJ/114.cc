#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;

struct XorBase {
  int64 a[64];
  int zero, n;
  XorBase() {
    memset(a, 0, sizeof(a));
    zero = n = 0;
  }
  void add(int64 x) {
    for (int i = 60; i >= 0; --i) if (x >> i & 1) {
      if (a[i]) x ^= a[i];
      else {
        a[i] = x;
        break;
      }
    }
    if (!x) zero = true;
  }
  void build() {
    for (int i = 60; i >= 0; --i) {
      for (int j = i - 1; j >= 0; --j) {
        if (a[i] >> j & 1) a[i] ^= a[j];
      }
    }
    for (int i = 0; i <= 60; ++i) {
      if (a[i]) a[n++] = a[i];
    }
  }
  int64 ask(int64 k) {
    k -= zero;
    int64 ret = 0;
    if (k > (1ll << n) - 1) return -1;
    for (int i = 0; i < n; ++i) {
      if (k >> i & 1) ret ^= a[i];
    }
    return ret;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  XorBase base;
  for (int i = 0; i < n; ++i) {
    int64 x;
    scanf("%lld", &x);
    base.add(x);
  }
  base.build();
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int64 k;
    scanf("%lld", &k);
    printf("%lld\n", base.ask(k));
  }
}

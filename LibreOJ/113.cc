#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;

struct XorBase {
  int64 a[64];
  XorBase() {
    memset(a, 0, sizeof(a));
  }
  void add(int64 x) {
    for (int i = 60; i >= 0; --i) if (x >> i & 1) {
      if (a[i]) x ^= a[i];
      else {
        a[i] = x;
        break;
      }
    }
  }
  int64 ask() {
    int64 ret = 0;
    for (int i = 60; i >= 0; --i) {
      ret = std::max(ret, ret ^ a[i]);
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
  printf("%lld\n", base.ask());
}

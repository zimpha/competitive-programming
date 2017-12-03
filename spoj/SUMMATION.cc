#include <cstdio>

const int mod = 1e8 + 7;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int ret = 0, p = 1;
    for (int i = 1; i < n; ++i) {
      p = p * 2 % mod;
    }
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      ret = (ret + x) % mod;
    }
    printf("Case %d: %lld\n", cas, 1ll * ret * p % mod);
  }
  return 0;
}

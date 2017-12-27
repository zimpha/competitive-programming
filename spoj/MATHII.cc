#include <cstdio>

using int64 = long long;

int main() {
  int cas = 0;
  for (int64 n; scanf("%lld", &n) == 1; ) {
    int64 ret = 0;
    for (int64 i = 1; i * i * i <= n; ++i) {
      ++ret;
      for (int j = i + 1; j <= n; ++j) {
        int64 k = n / i / j;
        if (k > j) ret += (k - j) * 6;
        else break;
      }
    }
    for (int64 i = 1; i * i <= n; ++i) {
      int64 k = n / i / i;
      if (k >= i) ret += (k - 1) * 3;
      else ret += k * 3;
    }
    printf("Case %d: %lld\n", ++cas, ret);
  }
  return 0;
}

#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, ret = 1;
    scanf("%lld", &n);
    for (int64 i = 2; i * i <= n; ++i) if (n % i == 0) {
      int c = 0;
      while (n % i == 0) c += 2, n /= i;
      ret *= c + 1;
    }
    if (n > 1) ret *= 3;
    printf("%lld\n", ret / 2);
  }
}

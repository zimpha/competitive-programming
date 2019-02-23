#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, a, b;
    scanf("%lld%lld%lld", &n, &a, &b);
    if (b >= 2 * a) printf("%lld\n", n * a);
    else printf("%lld\n", n * a + (b - a * 2) * (n / 2));
  }
}

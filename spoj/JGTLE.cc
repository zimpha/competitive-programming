#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    printf("Case %d: %lld\n", cas, a * (b * (b + 1) / 2) * (c * (c + 1) / 2));
  }
  return 0;
}

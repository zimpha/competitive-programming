#include <cstdio>

using i64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int p, q, a, b;
    scanf("%d%d%d%d", &p, &q, &a, &b);

    auto valid = [&](i64 x) {
      return (100 - p) * q * (b + x) <= (100 - q) * (1 + a * x) * p * b;
    };

    i64 left = 1, right = 1 << 30;
    while (left < right) {
      i64 mid = (left + right - 1) >> 1;
      if (valid(mid)) right = mid;
      else left = mid + 1;
    }
    if (right == (1 << 30)) puts("-1");
    else printf("%lld\n", left);
  }
  return 0;
}

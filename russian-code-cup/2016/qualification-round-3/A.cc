#include <cstdio>
#include <algorithm>

using ll = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    ll n = 1ll * a * b / c / c;
    if (n == 0) ++n;
    ll u = 1, ret = std::abs(1ll * a * b - 1ll * c * c);
    for (int i = 0; i < 2; ++i) {
      ll tmp = std::abs(1ll * a * b - 1ll * c * c * (n + i));
      if (tmp < ret) ret = tmp, u = i + n;
    }
    printf("%lld\n", 1ll * c * c * u);
  }
  return 0;
}

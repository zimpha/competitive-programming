#include <cstdio>
#include <cmath>

using ll = long long;

bool is_square(ll n) {
  ll x = sqrt(n);
  return x * x == n;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    ll n;
    scanf("%lld", &n);
    int ret = 0;
    for (ll i = 0; i * i * 2 <= n; ++i) {
      ret += is_square(n - i * i);
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

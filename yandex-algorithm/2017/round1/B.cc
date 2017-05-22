#include <bits/stdc++.h>

using ll = long long;

int main() {
  ll n, a;
  scanf("%lld%lld", &n, &a);
  ll s = n % 500;
  ll ret = 0;
  for (int i = 0; i < 500; ++i) {
    ll x = a + i, y = n - x;
    if (y < a) continue;
    ret = std::max(ret, (500 - x % 500) % 500 + (500 - y % 500) % 500);
  }
  printf("%lld\n", ret);
  return 0;
}

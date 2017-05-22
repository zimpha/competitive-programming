#include <bits/stdc++.h>

using ll = long long;

const int mod = 1000000000 + 7;

ll fac[200], inv[200];

ll pow_mod(ll a, ll n) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  ll tot = 2017201720172018;
  ll block = tot / mod, rem = tot % mod;
  int f0 = 1, f1 = 1;
  int n = 2 * mod + 2;
  ll cnt[200];
  memset(cnt, 0, sizeof(cnt));
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= 150; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = pow_mod(fac[i], mod - 2);
  }
  for (int i = 0; i < n; ++i) {
    int t = f0 + f1;
    f0 = f1, f1 = t % mod;
    ll r = 1;
    if (i % 1000000 == 0) std::cout << i << std::endl;
    ll mul = block + (i < rem);
    for (int k = 1; k <= 150 && k <= f1; ++k) {
      r = r * (f1 - k + 1) % mod;
      cnt[k] += r * mul % mod;;
      if (cnt[k] >= mod) cnt[k] -= mod;
    }
  }
  ll ret = 0;
  for (int i = 1; i <= 150; ++i) {
    ret = (ret + inv[i] * cnt[i] % mod) % mod;
  }
  std::cout << ret << std::endl;
  return 0;
}

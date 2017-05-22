#include <bits/stdc++.h>

using ll = long long;

const int N = 2289440;
ll phi[N];

void sieve() {
  for (int i = 0; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) {
    if (phi[i] != i) continue;
    for (int j = i; j < N; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
}

ll F(ll n) {
  ll ret = 1;
  n -= 1;
  if (!n) return ret + 1;
  ll s = 0, x = 3;
  for (; ; ++x) {
    if (s + x * phi[x] / 2 > n) break;
    ret += phi[x];
    s += x * phi[x] / 2;
  }
  if (s < n) {
    ll last = 1;
    for (ll i = 1; i * 2 <= x; ++i) {
      if (std::__gcd(i, x) == 1) last = i;
    }
    ret += (n - s) / x * 2;
    s = (n - s) % x;
    if (s >= x - last) ret += 1;
  }
  return ret + 1;
}

int main() {
  sieve();
  printf("%lld\n", F(1));
  printf("%lld\n", F(3));
  printf("%lld\n", F(9));
  printf("%lld\n", F(11));
  printf("%lld\n", F(100));
  printf("%lld\n", F(50000));
  printf("%lld\n", F(1000000000000000000ll));
  return 0;
}

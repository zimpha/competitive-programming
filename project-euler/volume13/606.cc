#include <bits/stdc++.h>

using ll = long long;

inline ll sqr(ll x) {return x * x;}
inline ll cub(ll x) {return x * x * x;}

const int SZ = 100000000, mod = 1e9;
int pi[SZ], pl[SZ], p3[SZ], m;

void sieve() {
  m = 0; for (int i = 2; i < SZ; ++ i) pi[i] = 1;
  for (int i = 2; i < SZ; ++i) {
    if (pi[i]) pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i < SZ; ++j) {
      pi[pl[j] * i] = 0;
      if (i % pl[j] == 0) break;
    }
  }
  for (int i = 0; i < m; ++i) {
    p3[i] = 1ll * pl[i] * pl[i] % mod * pl[i] % mod;
  }
  for (int i = 2; i < SZ; ++ i) {
    if (pi[i]) pi[i] = 1ll * i * i % mod * i % mod;
    pi[i] += pi[i - 1];
    pi[i] %= mod;
  }
}

ll sum3(ll n) {
  ll x = n, y = n + 1;
  if (x % 2 == 0) x >>= 1;
  else y >>= 1;
  x %= mod, y %= mod;
  x = x * y % mod;
  return x * x % mod - 1;
}

std::map<ll, ll> cache[1000000];

ll S(ll v, int x) {
  if (x == 0) return (sum3(v) - 8 * sum3(v / 2) % mod + mod) % mod;
  if (cache[x].count(v)) return cache[x][v];
  ll ret = S(v, x - 1);
  ret -= p3[x] * (S(v / pl[x], x - 1) - S(pl[x] - 1, x - 1)) % mod;
  ret %= mod; ret += mod; ret %= mod;
  return cache[x][v] = ret;
}

ll count(ll n) {
  if (n < SZ) return pi[n];
  int i = 0;
  while (1ll * pl[i] * pl[i] <= n) ++i;
  return S(n, i - 1);
}

ll solve(ll n) {
  ll ret = 0;
  /*
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (1ll * pl[i] * pl[j] > n) break;
      printf("%d %d\n", pl[i], pl[j]);
      ret += 1ll * p3[i] * p3[j] % mod;
      ret %= mod;
    }
  }
  return ret;*/
  for (int i = 0; 1ll * pl[i] * pl[i] <= n; ++i) {
    ret += 1ll * p3[i] * (count(n / pl[i]) - count(pl[i])) % mod;
    ret %= mod;
  }
  return ret;
}

int main() {
  sieve();
  std::cout << solve(100) << std::endl;
  std::cout << solve(10000) << std::endl;
  std::cout << solve(1000000000000ll) << std::endl;
  return 0;
}

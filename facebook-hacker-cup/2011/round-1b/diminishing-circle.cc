#include <cstdio>
#include <map>

const int K = 10000 + 10;

using ll = long long;

std::map<ll, ll> g[K];

ll solve(ll n, ll k) {
  if (g[k].count(n)) return g[k][n];
  if (n == 1 || k == 1) return 0;
  if (n < k) g[k][n] = (solve(n - 1, k) + k) % n;
  ll nn = n - n / k;
  ll t = solve(nn, k);
  return g[k][n] = k * (((t - n % k) % nn + nn) % nn) / (k - 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    ll n, k;
    scanf("%lld%lld", &n, &k);
    printf("Case #%d: %lld\n", cas, solve(n, k + 1) + 1);
  }
  return 0;
}

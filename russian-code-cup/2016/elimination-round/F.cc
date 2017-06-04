#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;
const int M = 1000000;

ll gcd(ll a, ll b) {
  return !b ? a : gcd(b, a % b);
}

std::pair<ll, ll> exgcd(ll a, ll b) {
  std::pair<ll, ll> p{1, 0}, q{0, 1};
  while (b > 0) {
    ll z = a / b;
    std::pair<ll, ll> t{p.first - z * q.first, p.second - z * q.second};
    p = q;
    q = t;
    ll x = b;
    b = a % b;
    a = x;
  }
  return p;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    ll d;
    scanf("%d%lld", &n, &d);
    std::vector<ll> a(n), pre(n + 1);
    pre[0] = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      pre[i + 1] = gcd(pre[i], a[i]);
    }
    if (d % pre[n]) {
      puts("NO");
      continue;
    }
    std::vector<ll> x(n);
    for (int i = n - 1; i >= 1; --i) {
      std::pair<ll, ll> res = exgcd(a[i], pre[i]);
      ll u = res.first, v = res.second;
      ll tmp = d / pre[i + 1];
      ll w = pre[i] / pre[i + 1];
      u = u * tmp % w;
      for (int j = -2; j <= 2; ++j) {
        ll s = u + j * w;
        if (!s || std::abs(s) > M) continue;
        ll nxt = d - a[i] * s;
        if ((i == 1 && !nxt) || std::abs(nxt / pre[i]) > M) continue;
        x[i] = s;
        d = nxt;
        break;
      }
    }
    x[0] = d / a[0];
    puts("YES");
    for (auto &&e: x) printf("%lld ", e);
    puts("");
  }
  return 0;
}

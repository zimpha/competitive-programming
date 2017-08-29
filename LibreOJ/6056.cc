#include <cstdio>
#include <cassert>
#include <map>

using ll = long long;

const int mod = 1e9 - 401, N = 10000;
const int pf[] = {2, 13, 5281, 7283};

int fac[N], inv[N];

ll pow_mod(ll a, ll n, ll m) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

void prepare(int n) {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < n; ++i) {
    fac[i] = fac[i - 1] * i % n;
  }
  inv[1] = 1;
  for (int i = 2; i < n; ++i) {
    inv[i] = (n - n / i) * inv[n % i] % n;
  }
}

std::pair<ll, ll> reduce(int n, int p) {
  ll a = 1, b = 0;
  for (ll i = p; i <= n; i *= p) {
    b += n / i;
  }
  for (int i = n; i; i /= p) {
    a = 1ll * a * fac[i % p] % p;
  }
  return {a, b};
}

int calc(int n, int d, int p) {
  auto a = reduce(n, p);
  auto b = reduce(d, p);
  auto c = reduce(n / d, p);
  c.first = pow_mod(c.first, d, p);
  c.second *= d;
  return a.first * inv[b.first] % p * inv[c.first] % p * (a.second - b.second - c.second ? 0 : 1);
}

ll solve(int n) {
  int ret = 0;
  for (int i = 0; i < 4; ++i) {
    int p = pf[i];
    int tmp = 0;
    prepare(p);
    for (int d = 1; d * d <= n; ++d) {
      if (n % d == 0) {
        tmp += calc(n, d, p);
        if (d * d != n) {
          tmp += calc(n, n / d, p);
        }
        tmp %= p;
      }
    }
    ret += 1ll * (mod - 1) / p * tmp % (mod - 1) * inv[(mod - 1) / p % p] % (mod - 1);
    ret %= mod - 1;
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    int ret = solve(n);
    printf("%lld\n", pow_mod(m, ret, mod));
  }
  return 0;
}

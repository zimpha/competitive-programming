#include <bits/stdc++.h>

using LL = long long;

void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}
LL crt(int n, LL *c, LL *m) {
  LL M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    LL x, y, g, tm = M / m[i];
    exgcd(tm, m[i], g, x, y);
    ans = (ans + tm * x * c[i] % M) % M;
  }
  return (ans + M) % M;
}

namespace BC {
  std::vector<int> fac, inv;
  void lucas_init(int m) {
    fac.assign(m, 1);
    inv.assign(m, 1);
    for (int i = 2; i < m; ++i) {
      fac[i] = 1ll * i * fac[i - 1] % m;
      inv[i] = 1ll * (m - m / i) * inv[m % i] % m;
    }
  }
  inline int lucas_binom(int n, int m, int p) {
    return 1ll * fac[n] * inv[fac[m]] * inv[fac[n - m]] % p;
  }
  int lucas(LL n, LL m, int p) {
    if (!n && !m) return 1;
    int a = n % p, b = m % p;
    if (a < b) return 0;
    return 1ll * lucas(n / p, m / p, p) * lucas_binom(a, b, p) % p;
  }
}

LL run() {
  std::vector<int> mp(5000, 0), p, v;
  for (int i = 2; i < 5000; ++i) if (!mp[i]) {
    if (i > 1000) p.push_back(i);
    for (int j = i; j < 5000; j += i) mp[j] = 1;
  }
  const LL n = 1000000000000000000ll, m = 1000000000ll;
  for (auto &&x: p) {
    BC::lucas_init(x);
    v.push_back(BC::lucas(n, m, x));
  }
  LL ret = 0;
  for (size_t i = 0; i < p.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      for (size_t k = 0; k < j; ++k) {
        LL c[3] = {v[i], v[j], v[k]}, m[3] = {p[i], p[j], p[k]};
        ret += crt(3, c, m);
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

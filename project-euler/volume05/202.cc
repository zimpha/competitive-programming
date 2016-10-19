#include <bits/stdc++.h>

using LL = long long;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

LL mod_inv(LL a, LL m) {
  LL d, x, y;
  exgcd(a, m, d, x, y);
  return d == 1 ? (x % m + m) % m : -1;
}

std::vector<LL> congruence_equation(LL a, LL b, LL m) {
  std::vector<LL> ret;
  LL g = gcd(a, m), x;
  if (b % g != 0) return ret;
  a /= g, b /= g;
  x = mod_inv(a, m / g);
  for (int k = 0; k < g; ++k) {
    ret.push_back((x * b + m / g * k) % m);
  }
  return ret;
}


LL run(LL n) {
  n = (n + 3) / 2; // n mod 3 = 1
  LL ret = 0, x = 3 - n % 3;
  std::vector<LL> fac;
  LL m = n;
  for (LL i = 2; i * i <= m; ++i) if (m % i == 0) {
    fac.push_back(i);
    while (m % i == 0) m /= i;
  }
  if (m > 0) fac.push_back(m);
  ret = (n - x - 1) / 3;
  m = fac.size();
  for (int msk = 1; msk < (1 << m); ++msk) {
    LL mod = 1, sgn = 1;
    for (int i = 0; i < m; ++i) {
      if (msk >> i & 1) {
        mod *= fac[i], sgn *= -1;
      }
    }
    LL val = 0;
    auto res = congruence_equation(3, (mod - x) % mod, mod);
    for (auto &&e: res) {
      LL upp = std::max(0ll, n - e * 3 - x - 1);
      val += upp / (mod * 3);
    }
    ret += val * sgn;
  }
  return ret;
}

int main() {
  assert(run(1000001) == 80840);
  std::cout << run(12017639147ll) << std::endl;
  return 0;
}

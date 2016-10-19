#include <bits/stdc++.h>

using LL = long long;

LL mul_mod(LL a, LL b, LL mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  LL k = (LL)((long double)a * b / mod);
  LL res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

LL pow_mod_LL(LL a, LL n, LL m) {
  LL res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(LL n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (~n & 1) return false;
  const int u[] = {2,325,9375,28178,450775,9780504,1795265022,0};
  LL e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
  while (~e & 1) e >>= 1, ++c;
  for (int i = 0; u[i]; ++i) {
    if (n <= u[i]) return true;
    a = pow_mod_LL(u[i], e, n);
    if (a == 1) continue;
    for (int j = 1; a != n - 1; ++j) {
      if (j == c) return false;
      a = mul_mod(a, a, n);
    }
  }
  return true;
}

int run(int n) {
  std::vector<int> p;
  std::vector<bool> mark(30, 0);
  for (int i = 2; i < 30; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j < 30; j += i) mark[j] = 1;
  }
  int m = p.size();
  std::vector<int> f; f.push_back(1);
  std::vector<int> adm;
  for (int i = 0; i < m; ++i) {
    int val = 1;
    std::vector<int> g;
    for (; ;) {
      if (1ll * val * p[i] > n) break;
      val *= p[i];
      for (auto &e: f) {
        if (1ll * val * e > n) break;
        g.push_back(val * e);
      }
    }
    f.swap(g);
    std::sort(f.begin(), f.end());
    for (auto &e: f) adm.push_back(e);
  }
  std::sort(adm.begin(), adm.end());
  std::set<int> pse;
  for (auto &e: adm) {
    for (int i = 2; ; ++i) {
      if (is_prime(e + i)) {
        pse.insert(i);
        break;
      }
    }
  }
  return accumulate(pse.begin(), pse.end(), 0ll);
}

int main() {
  std::cout << run(1000000000) << std::endl;
  return 0;
}

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

bool is_proof(LL n) {
  for (LL pw = 1; pw <= n; pw *= 10) {
    int o = n / pw % 10;
    for (int i = 0; i < o; ++i) {
      if (is_prime(n - pw * (i + 1))) return false;
    }
    for (int i = o + 1; i < 10; ++i) {
      if (is_prime(n + pw * (i - o))) return false;
    }
  }
  return true;
}

bool is_200(LL n) {
  static char s[20];
  sprintf(s, "%lld", n);
  for (int i = strlen(s) - 1; i >= 2; --i) {
    if (s[i] == '0' && s[i - 1] == '0' && s[i - 2] == '2') return true;
  }
  return false;
}

LL run(int n) {
  std::vector<int> p;
  std::vector<bool> mark(1e6, 1);
  for (int i = 2; i < 1e6; ++i) if (mark[i]) {
    p.push_back(i);
    for (int j = i; j < 1e6; j += i) mark[j] = 0;
  }
  const LL upp = (LL)1e13;
  std::vector<LL> res;
  for (int i = 0; i < p.size() && 1ll * p[i] * p[i] * p[i] <= upp; ++i) {
    LL a = 1ll * p[i] * p[i] * p[i];
    for (int j = 0; j < p.size() && a * p[j] * p[j] <= upp; ++j) if (i != j) {
      if (is_200(a * p[j] * p[j]) && is_proof(a * p[j] * p[j])) {
        res.push_back(a * p[j] * p[j]);
      }
    }
  }
  std::sort(res.begin(), res.end());
  std::cout << res.size() << std::endl;
  return res[n - 1];
}

int main() {
  std::cout << run(200) << std::endl;
  return 0;
}

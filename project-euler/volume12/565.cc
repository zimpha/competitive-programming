#include <bits/stdc++.h>

using LL = long long;

inline LL mul_mod(LL a, LL b, LL mod) {
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
  const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
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

LL run(LL n, LL m) {
  int upp = sqrt(n);
  std::vector<int> prime_list, mark(upp, 0);
  for (int i = 2; i < upp; ++i) if (!mark[i]) {
    prime_list.push_back(i);
    for (int j = i; j < upp; j += i) mark[j] = true;
  }
  std::vector<std::pair<LL, LL>> chunk;
  for (int i = 2; i * m - 1 <= n; i += 2) {
    if (is_prime(i * m - 1)) chunk.push_back({i * m - 1, i * m - 1});
  }
  for (auto &&p: prime_list) {
    LL now = 1, pw = 1;
    for (int e = 1; ; ++e) {
      pw *= p;
      now += pw;
      if (pw > n) break;
      if (now % m == 0 && e > 1) {
        chunk.push_back({pw, p});
      }
    }
  }
  auto sum = [&](LL d) {
    LL m = n / d;
    return m * (m + 1) / 2 * d;
  };
  std::sort(chunk.begin(), chunk.end());
  LL ret = 0;
  for (size_t i = 0; i < chunk.size(); ++i) {
    LL pw = chunk[i].first, p = chunk[i].second;
    ret += sum(pw);
    if (pw <= n / p) ret -= sum(pw * p);
    for (size_t j = i + 1; j < chunk.size(); ++j) {
      int q = chunk[j].second;
      if (chunk[j].first > n / pw) break;
      ret -= sum(pw * chunk[j].first);
    }
  }
  return ret;
}

int main() {
  std::cout << run(20, 7) << std::endl;
  std::cout << run(1000000, 2017) << std::endl;
  std::cout << run(1000000000, 2017) << std::endl;
  std::cout << run(100000000000ll, 2017) << std::endl;
  return 0;
}

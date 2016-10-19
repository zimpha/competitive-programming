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

const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, -1, 1, -1, 1};

LL S(LL row) {
  std::vector<LL> r[5];
  row -= 2;
  for (int i = 0; i < 5; ++i, ++row) {
    LL s = row * (row - 1) / 2 + 1;
    r[i].resize(row);
    for (int j = 0; j < row; ++j, ++s) {
      if (is_prime(s)) r[i][j] = s;
      else r[i][j] = -s;
    }
  }
  std::set<LL> res;
  for (int i = 1; i <= 3; ++i) {
    for (size_t j = 0; j < r[i].size(); ++j) {
      if (r[i][j] < 0) continue;
      std::vector<std::pair<LL, int>> primes;
      for (int k = 0; k < 8; ++k) {
        int x = i + dx[k], y = j + dy[k];
        if (y == -1 || r[x].size() == y) continue;
        if (r[x][y] > 0) primes.push_back(std::make_pair(r[x][y], x));
      }
      if (primes.size() > 1) {
        if (i == 2) res.insert(r[i][j]);
        for (auto &p: primes) {
          if (p.second == 2) res.insert(p.first);
        }
      }
    }
  }
  return std::accumulate(res.begin(), res.end(), 0ll);
}

int main() {
  std::cout << S(8) << std::endl;
  std::cout << S(9) << std::endl;
  std::cout << S(10000) << std::endl;
  std::cout << S(5678027) + S(7208785)<< std::endl;
  return 0;
}

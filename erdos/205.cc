#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n, int64 m) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

inline int64 mul_mod(int64 a, int64 b, int64 m) {
  return a * b % m;
}

int64 Cipolla(int64 n, int64 p) {
  if (n % p == 0) return 0;
  if (p == 2) return (n & 1) ? 1 : -1;
  if (pow_mod(n, p >> 1, p) != 1) return -1;
  if (p & 2) return pow_mod(n, p + 1 >> 2, p);
  int64 a = 0;
  for (; pow_mod((a * a + p - n) % p, p >> 1, p) == 1; ++a);
  int64 I = (a * a + p - n) % p;
  int64 rx = 1, ry = 0, tx = a, ty = 1;
  auto mult = [=](int64 &a, int64 &b, int64 c, int64 d) {
    int64 tmp = (mul_mod(mul_mod(b, d, p), I, p) + mul_mod(a, c, p)) % p;
    b =(mul_mod(a, d, p) + mul_mod(b, c, p)) % p;
    a = tmp;
  };
  for (int64 c = p + 1 >> 1; c ; c >>= 1) {
    if (c & 1) mult(rx, ry, tx, ty);
    mult(tx, ty, tx, ty);
  }
  return std::min(rx, p - rx);
}

int64 solve(int n) {
  std::vector<int> mp(n + 2, 1), ps;
  for (int i = 2; i <= n + 1; ++i) {
    if (mp[i] == 1) {
      mp[i] = i;
      ps.push_back(i);
    }
    for (int j = 0, u = (n + 1) / i; j < ps.size() && ps[j] <= u; ++j) {
      mp[i * ps[j]] = ps[j];
      if (i % ps[j] == 0) break;
    }
  }
  for (int i = 2; i <= n + 1; ++i) {
    mp[i] = std::max(mp[i], mp[i / mp[i]]);
  }
  std::vector<int> ret(n + 1);
  std::vector<int64> value(n + 1);
  for (int i = 1; i <= n; ++i) {
    ret[i] = mp[i + 1];
    value[i] = (int64)i * i - i + 1;
  }
  int cnt = 0;
  for (auto &&p: ps) if (p > 2) {
    int64 sq = Cipolla(p - 3, p);
    int64 i2 = pow_mod(2, p - 2, p);
    if (sq == -1) {
      ++cnt;
      continue;
    }
    int64 k1 = (1 + sq) * i2 % p;
    int64 k2 = (1 + p - sq) * i2 % p;
    for (int i = k1; i <= n; i += p) if (value[i] % p == 0) {
      ret[i] = std::max(ret[i], p);
      while (value[i] % p == 0) value[i] /= p;
    }
    for (int i = k2; i <= n; i += p) if (value[i] % p == 0) {
      ret[i] = std::max(ret[i], p);
      while (value[i] % p == 0) value[i] /= p;
    }
  }
  int64 sum = 0;
  for (int i = 1; i <= n; ++i) {
    //printf("%lld\n", value[i]);
    sum += std::max<int64>(ret[i], value[i]) % mod;
  }
  return sum % mod;
}

int main() {
  printf("%lld\n", solve(10000000));
  return 0;
}

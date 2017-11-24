#include <iostream>
#include <vector>
#include <algorithm>

using int64 = long long;
using int128 = __int128;

const int mod = 1e9 + 7;

int128 pow_mod(int128 a, int128 n) {
  int64 r = 1;
  for (a %= mod; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

// XOR_{i=1}^{n} s_i = k, 0 <= s_i <= m
int128 C(int128 n, int128 m, int128 k) {
  if (m < 0) return 0;
  if (n == 0 || m == 0) return k == 0;
  int128 x = 1;
  while (x <= m) x *= 2;
  if (x <= k) return 0;
  int64 ret = (pow_mod(m + 1, n) - pow_mod(mod - 1, n) * pow_mod(x - m - 1, n) % mod + mod) * pow_mod(x, mod - 2) % mod;
  int64 t = (n & 1) ? C(n, x - m - 2, k ^ (x - 1)) : C(n, x - m - 2, k);
  return (ret + pow_mod(mod - 1, n) * t) % mod;
}

int64 S(int n) {
  std::vector<int128> F = {0, 1};
  for (int i = 2; i <= n; ++i) {
    F.push_back(F[i - 1] + F[i - 2]);
  }
  int128 ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      ret += C(F[j], F[i] - 1, 0);
    }
  }
  return ret % mod;
}

int main() {
  std::cout << S(6) << std::endl;
  std::cout << S(7) << std::endl;
  std::cout << S(92) << std::endl;
  return 0;
}

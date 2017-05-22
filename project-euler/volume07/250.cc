#include <bits/stdc++.h>

const int mod = 104060401;

long pow_mod(long a, long n) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

long run(long G, long L, long N) {
  std::vector<long> dvs(G + 1), f(G + 1);
  for (int i = 1; i <= G; ++i) {
    for (int j = i; j <= G; j += i) ++dvs[j];
  }
  for (int i = 1; i <= G; ++i) {
    f[i] = (f[i] + pow_mod(dvs[i], N)) % mod;
    for (int j = i * 2; j <= G; j += i) {
      f[j] = (f[j] + mod - dvs[j / i] * f[i] % mod) % mod;
    }
  }
  long ret = 0;
  for (int i = 1; i <= G; ++i) {
    long a = G, b = L / i;
    if (a > b) break;
    ret += (b - a + 1) % mod * f[i] % mod;
  }
  return ret % mod;
}

int main() {
  std::cout << run(10, 100, 1) << std::endl;
  std::cout << run(10, 100, 2) << std::endl;
  std::cout << run(10, 100, 3) << std::endl;
  std::cout << run(10, 100, 1000) << std::endl;
  std::cout << run(1000000, 1000000000000ll, 1000000000000000000ll) << std::endl;
  return 0;
}

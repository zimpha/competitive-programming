#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>

using int64 = long long;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

bool test(int64 g, int64 n, int64 phi, std::vector<int64> &u) {
  for (size_t i = 0; i < u.size(); ++i) {
    if (pow_mod(g, phi / u[i], n) == 1) return false;
  }
  return true;
}

int64 primitive_root(int64 n) {
  int64 phi = n - 1, m = phi;
  std::vector<int64> u;
  for (int64 i = 2; i * i <= m; ++i) if (m % i == 0) {
    u.push_back(i);
    while (m % i == 0) m /= i;
  }
  if (m > 1) u.push_back(m);
  for (int g = 1; ; ++g) {
    if (test(g, n, phi, u)) return g;
  }
  return -1;
}

int gcd(int x, int y) {
  return y ? gcd(y, x % y) : x;
}

int main() {
  int p, T;
  scanf("%d%d", &p, &T);
  std::vector<int> primes;
  int m = p - 1;
  for (int i = 2; i * i <= m; ++i) if (m % i == 0) {
    primes.push_back(i);
    while (m % i == 0) m /= i;
  }
  if (m > 1) primes.push_back(m);

  auto order = [&] (int x) {
    int m = p - 1;
    for (auto d: primes) {
      while (m % d == 0 && pow_mod(x, m / d, p) == 1) m /= d;
    }
    return (p - 1) / m % (p - 1);
  };

  for (int cas = 1; cas <= T; ++cas) {
    int n, zero = 0, g = 0;
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      if (x == 0) ++zero;
      else g = gcd(g, order(x));
    }
    int target;
    scanf("%d", &target);
    if (target == 0) printf("%d\n", zero);
    else {
      target = order(target);
      if ((g == 0 && target == 0) || (g != 0 && target % g == 0)) puts("1");
      else puts("0");
    }
  }
  return 0;
}

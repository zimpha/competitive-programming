#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, k, p;
    scanf("%lld%lld%lld", &n, &k, &p);
    std::vector<int64> fac(p, 1), ifac(p, 1), inv(p, 1);
    for (int i = 2; i < p; ++i) {
      inv[i] = (p - p / i) * inv[p % i] % p;
      fac[i] = fac[i - 1] * i % p;
      ifac[i] = ifac[i - 1] * inv[i] % p;
    }
    int64 ret = 1;
    for (int64 a = n + 1, b = k + 1; a || b; a /= p, b /= p) {
      int n = a % p, m = b % p;
      if (n < m) ret = 0;
      else ret = ret * fac[n] * ifac[n - m] % p * ifac[m] % p;
    }
    printf("%lld\n", ret);
  }
  return 0;
}

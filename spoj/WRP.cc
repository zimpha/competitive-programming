#include <cstdio>
#include <vector>

using int64 = long long;

constexpr int mod = 1e9 + 7;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &k, &m);
    std::vector<int64> fac(n + 1, 1), ifac(n + 1, 1), inv(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
      fac[i] = fac[i - 1] * i % mod;
      inv[i] = (mod - mod / i) * inv[mod % i] % mod;
      ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    int64 ret = 0;
    for (int i = 0; i <= k && n - i * m >= k; ++i) {
      int64 add = fac[k] * ifac[i] % mod * ifac[k - i] % mod * 
                  fac[n - i * m - 1] % mod * ifac[k - 1] % mod * ifac[n - i * m - k] % mod;
      if (i & 1) ret += mod - add;
      else ret += add;
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}

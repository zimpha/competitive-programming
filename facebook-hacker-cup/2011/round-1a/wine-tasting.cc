#include <cstdio>
#include <vector>

const int mod = 1051962371;

int pow_mod(int a, int n, int mod) {
  int r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = 1ll * r * a % mod;
    a = 1ll * a * a % mod;
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int G, C;
    scanf("%d%d", &G, &C);
    std::vector<int> fac(G + 1, 1);
    std::vector<int> inv(G + 1, 1);
    for (int i = 1; i <= G; ++i) {
      fac[i] = 1ll * fac[i - 1] * i % mod;
      inv[i] = pow_mod(fac[i], mod - 2, mod);
    }
    std::vector<int> dp(G + 1, 1);
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= G; ++i) {
      dp[i] = 1ll * (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
    }
    int ret = 0;
    for (int i = C; i <= G; ++i) {
      ret = (ret + 1ll * fac[G] * inv[i] % mod * inv[G - i] % mod * dp[G - i]) % mod;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

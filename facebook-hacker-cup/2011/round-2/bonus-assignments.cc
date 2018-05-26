#include <cstdio>
#include <vector>

const int mod = 1e9 + 7;

using ll = long long;

int pow_mod(int a, int n) {
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
    int n, a, b, c, d;
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    std::vector<ll> g(d + 1, 0);
    for (int i = d; i >= 1; --i) {
      int x = b / i - (a - 1) / i;
      int y = d / i - (c - 1) / i;
      int z = c <= b ? b / i - (c - 1) / i : 0;
      if (a <= d) g[i] += pow_mod(d / i - (a - 1) / i, n);
      if (a <= c - 1) g[i] -= pow_mod((c - 1) / i - (a - 1) / i, n);
      if (b + 1 <= d) g[i] -= pow_mod(d / i - b / i, n);
      if (b + 1 <= c - 1) g[i] += pow_mod((c - 1) / i - b / i, n);
      g[i] %= mod; g[i] += mod; g[i] %= mod;
      for (int j = i + i; j <= d; j += i) {
        g[i] = (g[i] - g[j] + mod) % mod;
      }
    }
    printf("Case #%d: %d\n", cas, g[1]);
  }
  return 0;
}

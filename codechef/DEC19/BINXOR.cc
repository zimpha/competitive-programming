#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10, mod = 1e9 + 7;

char a[N], b[N];
int64 fac[N], ifac[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d%s%s", &n, a, b);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fac[i] = fac[i - 1] * i % mod;
      ifac[i] = pow_mod(fac[i], mod - 2);
    }
    int ca[2] = {0, 0};
    int cb[2] = {0, 0};
    for (int i = 0; i < n; ++i) ca[a[i] - '0']++;
    for (int i = 0; i < n; ++i) cb[b[i] - '0']++;
    int64 ret = 0;
    int mx = std::min(ca[0], cb[1]) + std::min(ca[1], cb[0]);
    for (int one = 0; one <= mx; ++one) {
      int x = (one + ca[0] - cb[0]) / 2;
      int y = (one - ca[0] + cb[0]) / 2;
      if (x + y == one && x >= 0 && y >= 0 && x - y == ca[0] - cb[0]) {
        ret += fac[n] * ifac[one] % mod * ifac[n - one] % mod;
      }
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using int64 = long long;

constexpr int mod = 1000000037;
constexpr int mx = 421, my = 563, mz = 4219;

template<int64 mod>
struct binom {
  int fac[mod], inv[mod], rv[mod];
  void init() {
    fac[0] = inv[0] = fac[1] = inv[1] = rv[1] = 1;
    for (int i = 2; i < mod; ++i) {
      rv[i] = (int64)rv[mod % i] * (mod - mod / i) % mod;
      fac[i] = (int64)fac[i - 1] * i % mod;
      inv[i] = (int64)inv[i - 1] * rv[i] % mod;
    }
  }
  int64 get_mod() const {
    return mod;
  }
  int64 lucas(int64 n, int64 m) {
    if (n == 0 && m == 0) return 1;
    int64 a = n % mod, b = m % mod;
    if (b > a) return 0;
    return lucas(n / mod, m / mod) * fac[a] * inv[b] * inv[a - b] % mod;
  }
  int64 calc(int64 p, int64 q) {
    return lucas(p + q, q);
  }
};

int64 pow_mod(int64 a, int64 b, int64 mod) {
  int64 ret = 1;
  for (a %= mod; b; b >>= 1) {
    if (b & 1) ret = ret * a % mod;
    a = a * a % mod;
  }
  return ret;
}

binom<mx> x;
binom<my> y;
binom<mz> z;

void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

int64 crt(int n, int64 *c, int64 *m) {
  int64 M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    int64 x, y, g, tm = M / m[i];
    exgcd(tm, m[i], g, x, y);
    ans = (ans + tm * x * c[i] % M) % M;
  }
  return (ans + M) % M;
}

int main() {
  x.init();
  y.init();
  z.init();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, A, B, a, b;
    scanf("%d%d%d%d%d", &n, &a, &b, &A, &B);
    n -= b - 1;
    if (n < 0) puts("0");
    else if (n == 0) puts("1");
    else if (a == b) {
      int t = n % a;
      if (t == 0) printf("%lld\n", pow_mod(A + B, n / a, mod));
      else printf("0\n");
    } else {
      int64 rx = 0, ry = 0, rz = 0, ret = 0;
      for (int p, q = n / b; q >= 0; -- q) {
        if ((n - b * q) % a == 0) {
          p = (n - b * q) / a;
          rx = (rx + pow_mod(A, p, mx) * pow_mod(B, q, mx) * x.calc(p, q)) % mod;
          ry = (ry + pow_mod(A, p, my) * pow_mod(B, q, my) * y.calc(p, q)) % mod;
          rz = (rz + pow_mod(A, p, mz) * pow_mod(B, q, mz) * z.calc(p, q)) % mod;
        }
      }
      int64 c[3] = {rx, ry, rz};
      int64 m[3] = {mx, my, mz};
      printf("%lld\n", crt(3, c, m));
    }
  }
  return 0;
}

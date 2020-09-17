#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using int64 = long long;

const int N = 10000 + 10;
const int mod = 1e9 + 7;

int r[3];
char s[3][N];
int64 sum[2][N];
int64 fac[N], ifac[N];
int64 bs[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

inline int64 binom(int n, int m) {
  assert(m <= n);
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < 3; ++i) {
    scanf("%d%s", &r[i], s[i]);
  }
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  int64 ret = 0;
  for (int i = 0; i <= r[0]; ++i) ret += binom(n, i);
  for (int i = 0; i <= r[1]; ++i) ret += binom(n, i);
  for (int i = 0; i <= r[2]; ++i) ret += binom(n, i);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < i; ++j) {
      int zero = 0, one = 0;
      for (int k = 0; k < n; ++k) {
        zero += s[i][k] == s[j][k];
        one += s[i][k] != s[j][k];
      }
      bs[0] = binom(one, 0);
      for (int b = 1; b <= one; ++b) bs[b] = (bs[b - 1] + binom(one, b)) % mod;
      // a + b <= r[i], a + one - b <= r[j];
      for (int a = 0; a <= r[i] && a <= zero; ++a) {
        int u = std::max(0, a + one - r[j]), v = std::min(r[i] - a, one);
        if (u <= v) {
          int64 tmp = bs[v];
          if (u) tmp = tmp + mod - bs[u - 1];
          ret -= binom(zero, a) * tmp % mod;
        }
      }
    }
  }
  // s1: 0011
  // s2: 0101
  //     ABCD
  // A+B+C+D <= r0
  // A+B+c10-C+c11-D <= r1
  // A+c01-B+C+c11-D <= r2
  // A+B <= r1-c10-c11+C+D, A+B <= r0-(C+D)
  // A-B <= r2-c01-c11+D-C
  int c[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < n; ++i) {
    c[s[1][i] != s[0][i]][s[2][i] != s[0][i]]++;
  }
  int64 *x = sum[0], *y = sum[1];
  int delta_bound = std::max(0, r[2] - c[0][1] - c[1][1]) + r[0];
  for (int delta = -r[0]; delta <= delta_bound; ++delta) {
    int ra = std::min(std::min(r[0], c[0][1]) + delta, std::min(r[0], c[0][0]));
    if (r[0] + delta >= 0) ra = std::min(ra, (r[0] + delta) / 2);
    int la = std::max(0, delta);
    if (la <= ra) {
      for (int i = 0; i <= r[0]; ++i) y[i] = 0;
      for (int A = la; A <= ra; ++A) {
        int B = A - delta;
        assert(0 <= B && B <= r[0] && B <= c[0][1] && A + B <= r[0]);
        y[A + B] += binom(c[0][0], A) * binom(c[0][1], B) % mod;
      }
      for (int i = 1; i <= r[0]; ++i) {
        y[i] = (y[i] + y[i - 1]) % mod;
      }
      for (int i = 0; i <= r[0]; ++i) {
        y[i] = (y[i] + x[i]) % mod;
      }
    } else {
      std::swap(x, y);
    }
    int delta_d = delta + c[0][1] + c[1][1] - r[2];
    int rc = std::min(std::min(r[0], c[1][0]), std::min(r[0], c[1][1]) - delta_d);
    if (r[0] - delta_d >= 0) rc = std::min(rc, (r[0] - delta_d) / 2);
    int lc = std::max(0, -delta_d);
    for (int C = lc; C <= rc; ++C) {
      int D = delta_d + C;
      assert(0 <= D && D <= r[0] && D <= c[1][1] && C + D <= r[0]);
      int bound = std::min(r[1] - c[1][0] - c[1][1] + C + D, r[0] - C - D);
      if (bound >= 0) {
        ret += binom(c[1][0], C) * binom(c[1][1], D) % mod * y[bound] % mod;
      }
    }
    ret %= mod;
    std::swap(x, y);
  }
  printf("%lld\n", ret);
  return 0;
}

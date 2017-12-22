#include <cstdio>
#include <algorithm>

using int64 = long long;

const int period = 2e9 + 16, mod = 1e9 + 7;
const int U = 1e6 + 10;

void fib(int64 n, int64 &x, int64 &y) {// store in x, n-th
  if (n == 0) {
    x = 0, y = 1;
    return;
  } else if (n & 1) {
    fib(n - 1, y, x);
    y += x;
    if (y >= mod) y -= mod;
  } else {
    int64 a, b;
    fib(n >> 1, a, b);
    y = (a * a + b * b) % mod;
    x = (a * b + a * (b - a + mod)) % mod;
  }
}

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 cnt[U], f[U];

int main() {
  int mx = 0, n;
  int64 k;
  scanf("%d%lld", &n, &k);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x]++;
    mx = std::max(mx, x);
  }
  int64 ret = 0;
  for (int i = mx; i >= 1; --i) {
    int64 total = cnt[i];
    for (int j = i + i; j <= mx; j += i) {
      f[i] -= f[j];
      total += cnt[j];
    }
    f[i] += total * (total - 1) / 2;
    if (f[i]) {
      int64 x, y, m = pow_mod(i, k, period);
      fib(m, x, y);
      ret += f[i] % mod * x % mod;
    }
  }
  printf("%lld\n", ret % mod);
  return 0;
}

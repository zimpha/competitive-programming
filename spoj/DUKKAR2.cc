#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

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
    int64 p;
    int n;
    scanf("%lld%d", &p, &n);
    std::vector<int64> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }
    std::vector<int64> f(n), g(n);
    f[0] = a[0] * (a[0] + 1) / 2 % mod;
    g[0] = (a[0] + 1) % mod;
    int64 pp = p * (p + 1) / 2 % mod, pw = 1;
    int64 prod = (a[0] + 1) % mod;
    for (int i = 1; i < n; ++i) {
      pw = pw * pp % mod;
      f[i] = a[i] * (a[i] + 1) / 2 % mod * pw % mod;
      g[i] = (a[i] + 1) * (f[i - 1] + g[i - 1]) % mod;
      prod = prod * (a[i] + 1) % mod;
    }
    int64 sub = (f[n - 1] + g[n - 1] - prod + mod) % mod;
    int64 ret = 0;
    pw = 1;
    for (int i = 0; i < n; ++i) {
      ret = (ret + a[i] * pw) % mod;
      pw = pw * p % mod;
    }
    ret = ret * (ret + 1) / 2 % mod;
    printf("%lld\n", (ret - sub + mod) % mod);
  }
  return 0;
}

#include <cstdio>
#include <vector>
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

int main() {
  int n, m, a, q;
  scanf("%d%d%d%d", &n, &m, &a, &q);
  int mod = 0, pw = 1;
  for (int i = 0; ; ++i) {
    mod += 1;
    pw = 1ll * pw * a % q;
    if (pw == 1) break;
  }
  std::vector<int64> fac(mod), inv(mod);
  fac[0] = inv[0] = 1;
  for (int i = 1; i < mod; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = pow_mod(fac[i], mod - 2, mod);
  }
  std::vector<int> res(n, 1);
  for (int i = 1; i < n; ++i) {
    res[i] = res[i - 1];
    if (i <= m) {
      res[i] += fac[m] * inv[i] % mod * inv[m - i] % mod;
      res[i] %= mod;
    }
  }
  std::reverse(res.begin(), res.end());
  for (int i = 0; i < n; ++i) {
    //printf("%d ", res[i]);
    printf("%d ", pow_mod(a, res[i], q));
  }
  puts("");
  return 0;
}
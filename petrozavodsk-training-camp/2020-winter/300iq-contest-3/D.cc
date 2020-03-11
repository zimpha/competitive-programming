#include <cstdio>

using int64 = long long;

const int N = 200;
const int mod = 998244353;

int fac[N], inv[N];
int a[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 dfs(int n, int rest, int bound) {
  int64 ret = 0;
  if (rest == 0) {
    int64 hook = 1, sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += a[i];
      for (int j = n - 1; j >= i; --j) {
        int last = (j == n - 1) ? 0 : a[j + 1];
        for (int k = last + 1; k <= a[j]; ++k) {
          hook = hook * inv[j - i + a[i] - k + 1] % mod;
        }
      }
    }
    hook = hook * fac[sum] % mod;
    return hook * hook % mod;
  }
  for (int i = (n == 1 ? bound : 1); i <= bound && i <= rest; ++i) {
    a[n] = i;
    ret += dfs(n + 1, rest - i, i);
  }
  return ret % mod;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i < N; ++i) {
    inv[i] = pow_mod(i, mod - 2);
    fac[i] = (int64)fac[i - 1] * i % mod;
  }
  int n;
  scanf("%d", &n);
  int ret = dfs(0, n, n / 2);
  printf("%d\n", ret);
  return 0;
}

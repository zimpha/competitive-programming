#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using int64 = long long;

const int N = 6000 + 10, mod = 1e9 + 7;

int s[N][N], mul[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int64 ret = 1;
  mul[0] = 1;
  for (int i = 1; i <= k * 2; ++i) {
    mul[i] = (int64)mul[i - 1] * (n - i + 1) % mod * pow_mod(i, mod - 2) % mod;
  }
  s[0][0] = 1;
  for (int i = 2; i <= k * 2; ++i) {
    for (int j = 1; j * 2 <= i; ++j) {
      s[i][j] = (int64)(i - 1) * (s[i - 1][j] + s[i - 2][j - 1]) % mod;
      if (i - j <= k) ret += (int64)s[i][j] * mul[i] % mod;
    }
  }
  printf("%lld\n", ret % mod);
  return 0;
}

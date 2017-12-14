#include <cstdio>
#include <algorithm>

using int64 = long long;

const int mod = 2333;

int binom[mod][mod], sum[mod][mod];

int64 lucas(int64 n, int64 m) {
  if (m == 0) return 1;
  return binom[n % mod][m % mod] * lucas(n / mod, m / mod) % mod;
}

int64 solve(int64 n, int64 m) {
  if (m < 0) return 0;
  m = std::min(n, m);
  if (n < mod) return sum[n][m];
  return (sum[n % mod][mod - 1] * solve(n / mod, m / mod - 1) + 
          sum[n % mod][m % mod] * lucas(n / mod, m / mod)) % mod;
}

int main() {
  for (int i = 0; i < mod; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  for (int i = 0; i < mod; ++i) {
    sum[i][0] = binom[i][0];
    for (int j = 1; j < mod; ++j) {
      sum[i][j] = (binom[i][j] + sum[i][j - 1]) % mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, k;
    scanf("%lld%lld", &n, &k);
    printf("%lld\n", solve(n, k));
  }
  return 0;
}

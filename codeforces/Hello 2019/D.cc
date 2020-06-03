#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>

using int64 = long long;

const int N = 1e4 + 10, mod = 1e9 + 7;

int64 dp[N][100], inv[200];
std::vector<std::pair<int64, int>> fac;


int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int64 n, k;
  scanf("%lld%lld", &n, &k);
  for (int64 i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      int c = 0;
      while (n % i == 0) n /= i, ++c;
      fac.emplace_back(i, c);
    }
  }
  for (int i = 1; i <= 100; ++i) inv[i] = pow_mod(i, mod - 2);
  if (n > 1) fac.emplace_back(n, 1);
  int64 ret = 1;
  for (auto &&e: fac) {
    memset(dp, 0, sizeof(dp));
    dp[0][e.second] = 1;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j <= e.second; ++j) {
        for (int l = 0; l <= j; ++l) {
          dp[i + 1][l] += dp[i][j] * inv[j + 1] % mod;
          dp[i + 1][l] %= mod;
        }
      }
    }
    int64 tmp = 0;
    for (int i = 0; i <= e.second; ++i) {
      tmp += pow_mod(e.first, i) * dp[k][i] % mod;
    }
    tmp %= mod;
    ret = ret * tmp % mod;
  }
  printf("%lld\n", ret);
  return 0;
}
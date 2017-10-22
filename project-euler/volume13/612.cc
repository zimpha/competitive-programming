#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using int64 = long long;

const int mod = 1000267129;

int64 pw[20], dp[20][20][2];
int64 binom[20][20];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void prepare() {
  for (int i = 0; i < 20; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  pw[0] = 1;
  for (int i = 1; i < 20; ++i) pw[i] = pw[i - 1] * 10;
  for (int i = 1; i < 20; ++i) {
    for (int j = 1; j <= i && j <= 10; ++j) {
      dp[i][j][0] = pow_mod(j, i);
      dp[i][j][1] = (j - 1) * pow_mod(j, i - 1) % mod;
      for (int k = 1; k < j; ++k) {
        dp[i][j][0] += mod - binom[j][k] * dp[i][k][0] % mod;
        dp[i][j][0] %= mod;
        dp[i][j][1] += mod - dp[i][k][1] * binom[j - 1][k - 1] % mod;
        dp[i][j][1] += mod - dp[i][k][0] * binom[j - 1][k] % mod;
        dp[i][j][1] %= mod;
      }
    }
  }
}

int64 calc(int n, int m) {
  int64 ret = 0;
  for (int a = 1; a <= 10 && a <= n; ++a) {
    for (int b = 1; a + b <= 10 && b <= m; ++b) {
      for (int mask = 0; mask < 3; ++mask) {
        int ea = mask & 1, eb = mask >> 1 & 1;
        if (!ea && a == 10) continue;
        if (!eb && b == 10) continue;
        int64 add = dp[n][a][ea] * dp[m][b][eb] % mod;
        if (ea) add = add * binom[9][a - 1] % mod * binom[10 - a][b] % mod;
        else if (eb) add = add * binom[9][b - 1] % mod * binom[10 - b][a] % mod;
        else add = add * binom[9][a] % mod * binom[9 - a][b] % mod;
        ret += add;
        ret %= mod;
      }
    }
  }
  if (n == m) {
    ret = ret * 500133565 % mod;
    int64 x = 9 * pw[n - 1], y = x - 1;
    if (x & 1) y >>= 1;
    else x >>= 1;
    x %= mod, y %= mod;
    ret = x * y % mod - ret + mod;
  } else {
    ret = 9 * pow_mod(10, n - 1) % mod * 9 * pow_mod(10, m - 1) % mod - ret + mod;
  }
  return ret % mod;
}

int64 f(int n) {
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      ret += calc(i, j);
    }
  }
  return ret % mod;
}

int main() {
  prepare();
  std::cout << f(2) << std::endl;
  std::cout << f(18) << std::endl;
  return 0;
}

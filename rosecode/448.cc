#include <vector>
#include <iostream>

using int64 = long long;
const int mod = 98765431;
const int64 inf = 1ll << 60;

int64 C(int n) {
  std::vector<int64> x(n + 1);
  for (int i = 0, r = 2; i <= n; ++i) {
    x[i] = 5000 + r % 1000;
    r = (int64)r * r % mod;
  }
}

int64 C_n3_fast(int n) {
  std::vector<int64> x(n + 1);
  for (int i = 0, r = 2; i <= n; ++i) {
    x[i] = 5000 + r % 1000;
    r = (int64)r * r % mod;
  }
  std::vector<std::vector<int64>> dp(n, std::vector<int64>(n, inf));
  for (int i = 0; i < n; ++i) dp[0][i] = 0;
  for (int l = 1; l < n; ++l) {
    for (int u = 0; u < l; ++u) {
      int v = l - u - 1;
      for (int k = 0; k < n - l; ++k) {
        dp[l][k] = std::min(dp[l][k], dp[u][k] + dp[v][k + u + 1] + x[k] * x[k + u + 1] * x[k + l + 1]);
      }
    }
  }
  return dp[n - 1][0];
}

int64 C_n3(int n) {
  std::vector<int64> x(n + 1);
  for (int i = 0, r = 2; i <= n; ++i) {
    x[i] = 5000 + r % 1000;
    r = (int64)r * r % mod;
  }
  std::vector<std::vector<int64>> dp(n, std::vector<int64>(n));
  for (int l = 2; l <= n; ++l) {
    for (int i = 0; i + l <= n; ++i) {
      int j = i + l - 1;
      dp[i][j] = inf;
      for (int k = i; k < j; ++k) {
        int64 now = dp[i][k] + dp[k + 1][j] + x[i] * x[k + 1] * x[j + 1];
        if (now < dp[i][j]) dp[i][j] = now;
      }
    }
  }
  return dp[0][n - 1];
}

int main() {
  std::cout << C_n3_fast(3) << std::endl;
  std::cout << C_n3_fast(10) << std::endl;
  std::cout << C_n3_fast(6543) << std::endl;
  return 0;
}

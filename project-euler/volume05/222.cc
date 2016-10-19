#include <bits/stdc++.h>

double dp[1 << 21][21];

int run() {
  for (int msk = 0; msk < (1 << 21); ++msk) {
    for (int i = 0; i < 21; ++i) dp[msk][i] = 1e9;
  }
  for (int i = 0; i < 21; ++i) dp[1 << i][i] = i + 30;
  for (int msk = 0; msk < (1 << 21); ++msk) {
    for (int i = 0; i < 21; ++i) if (msk >> i & 1) {
      for (int j = 0; j < 21; ++j) if (~msk >> j & 1) {
        int r1 = i + 30, r2 = j + 30;
        if (r1 < r2) std::swap(r1, r2);
        int c = r1 + r2, a = std::max(r1 - r2, 100 - r1 - r2);
        double cost = dp[msk][i] + sqrt(c * c - a * a);
        dp[msk | (1 << j)][j] = std::min(dp[msk | (1 << j)][j], cost);
      }
    }
  }
  double ret = 1e9;
  for (int i = 0; i < 21; ++i) {
    ret = std::min(ret, dp[(1 << 21) - 1][i] + i + 30);
  }
  return round(ret * 1000);
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

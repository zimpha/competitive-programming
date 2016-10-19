#include <bits/stdc++.h>

const int N = 1000;
typedef long double flt;

flt dp[N + 1][N + 1], p[N + 1];

flt L(flt f, int n) {
  return (9 * log(10) - n * log(1 - f)) / (log(1 + f * 2) - log(1 - f));
}

flt run(int n) {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (!dp[i][j]) continue;
      dp[i + 1][j] += dp[i][j] * 0.5;
      dp[i + 1][j + 1] += dp[i][j] * 0.5;
    }
  }
  for (int i = 0; i <= n; ++i) p[i] = dp[n][i];
  flt left = 0, right = 1;
  for (int i = 0; i < 1000; ++i) {
    flt m1 = left + (right - left) / 3;
    flt m2 = right - (right - left) / 3;
    flt val1 = L(m1, n), val2 = L(m2, n);
    if (val1 > val2) left = m1;
    else right = m2;
  }
  flt ret = 0;
  for (int k = (int)ceil(L(left, n)); k <= n; ++k) {
    ret += p[k];
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(1000) << std::endl;
  return 0;
}


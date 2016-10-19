#include <bits/stdc++.h>

long dp[20][140][400];

long run(int n) {
  dp[0][0][200] = 1;
  for (int i = 0; i < n; ++i) {
    for (int carry = 0; carry < 140; ++carry) {
      for (int sum = 0; sum < 400; ++sum) {
        if (!dp[i][carry][sum]) continue;
        for (int d = 0; d < 10; ++d) {
          int c = (carry + d * 137) / 10;
          int s = sum + (carry + d * 137) % 10 - d;
          dp[i + 1][c][s] += dp[i][carry][sum];
        }
      }
    }
  }
  long ret = 0;
  for (int c = 0; c < 140; ++c) {
    for (int s = 0; s < 400; ++s) {
      int cnt = 0;
      for (int n = c; n; n /= 10) cnt += n % 10;
      if (s + cnt == 200) ret += dp[n][c][s];
    }
  }
  return ret;
}

int main() {
  std::cout << run(18) << std::endl;
  return 0;
}

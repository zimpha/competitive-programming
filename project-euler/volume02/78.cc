#include <bits/stdc++.h>
using namespace std;
const int M = 1000000, T = 1000;

int sol(int n) {
  vector<int> dp(n), tmp(n);
  for (int i = -1000; i <= 1000; ++ i) {
    tmp[i + T] = i * (i * 3 - 1) / 2;
  }
  dp[0] = 1;
  for (int i = 1; i < n; ++ i) {
    dp[i] = 0;
    for (int j = 1; j <= i; ++ j) {
      if (tmp[j + T] <= i) {
        if (j & 1) dp[i] += dp[i - tmp[j + T]];
        else dp[i] -= dp[i - tmp[j + T]];
      }
      else break;
      if (tmp[T - j] <= i) {
        if (j & 1) dp[i] += dp[i - tmp[T - j]];
        else dp[i] -= dp[i - tmp[T - j]];
      }
      else break;
    }
    dp[i] %= M; dp[i] += M; dp[i] %= M;
  }
  for (int i = 1; i < n; ++ i) {
    if (dp[i] == 0) return i;
  }
  return -1;
}

int main() {
  cout << sol(100000) << endl;
  return 0;
}

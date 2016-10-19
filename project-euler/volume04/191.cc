#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dp[50][3][2];

LL run(int n) {
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int a = 0; a < 3; ++a) {
      for (int l = 0; l < 2; ++l) if (dp[i][a][l]) {
        dp[i + 1][0][l] += dp[i][a][l];
        if (a + 1 < 3) dp[i + 1][a + 1][l] += dp[i][a][l];
        if (l + 1 < 2) dp[i + 1][0][l + 1] += dp[i][a][l];
      }
    }
  }
  LL ret = 0;
  for (int a = 0; a < 3; ++a) {
    for (int l = 0; l < 2; ++l) {
      ret += dp[n][a][l];
    }
  }
  return ret;
}

int main() {
  cout << run(4) << endl;
  cout << run(30) << endl;
  return 0;
}

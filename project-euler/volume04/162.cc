#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dp[20][2][2][2];

LL run(int n) {
  LL ret = 0;
  for (int s = 1; s <= n; ++s) {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;
    for (int i = 0; i < s; ++i) {
      for (int msk = 0; msk < 8; ++msk) {
        int a = msk & 1, b = msk >> 1 & 1, c = msk >> 2;
        dp[i + 1][a][b][c] += dp[i][a][b][c] * 13;
        if (i) dp[i + 1][1][b][c] += dp[i][a][b][c];
        dp[i + 1][a][1][c] += dp[i][a][b][c];
        dp[i + 1][a][b][1] += dp[i][a][b][c];
      }
    }
    ret += dp[s][1][1][1];
  }
  return ret;
}

int main() {
  cout << hex << uppercase << run(16) << endl;
  return 0;
}

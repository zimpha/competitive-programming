#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dp[41][1024][10];

LL run(int s) {
  LL ret = 0;
  for (int n = 10; n <= s; ++n) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < 10; ++i) dp[1][1 << i][i] = 1;
    for (int i = 1; i < n; ++i) {
      for (int msk = 0; msk < 1024; ++msk) {
        for (int d = 0; d < 10; ++d) if (dp[i][msk][d]) {
          if (d > 0) dp[i + 1][msk | (1 << (d - 1))][d - 1] += dp[i][msk][d];
          if (d < 9) dp[i + 1][msk | (1 << (d + 1))][d + 1] += dp[i][msk][d];
        }
      }
    }
    for (int d = 0; d < 10; ++d) ret += dp[n][1023][d];
  }
  return ret;
}

int main() {
  cout << run(40) << endl;
  return 0;
}

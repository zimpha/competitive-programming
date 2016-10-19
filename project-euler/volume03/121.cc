#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100;
LL dp[MAXN][MAXN];

LL run(int n) {
  dp[1][0] = dp[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j) dp[i][j] += dp[i - 1][j - 1] * i;
    }
  }
  LL x = 0, y = 0;
  for (int i = 0; i <= n; ++i) {
    if (i < (n + 1) / 2) x += dp[n][i];
    y += dp[n][i];
  }
  return y / x;
}

int main() {
  cout << run(4) << endl;
  cout << run(15) << endl;
  return 0;
}

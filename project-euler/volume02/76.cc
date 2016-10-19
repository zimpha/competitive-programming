#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> dp(n + 1, 0); dp[0] = 1;
  for (int i = 1; i <= n; ++ i) {
    for (int j = i; j <= n; ++ j) {
      dp[j] += dp[j - i];
    }
  }
  return dp[n] - 1;
}

int main() {
  cout << sol(5) << endl;
  cout << sol(100) << endl;
  return 0;
}

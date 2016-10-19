#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> vs(n, 1); vs[0] = vs[1] = 0;
  vector<int> pl;
  vector<int> dp(n, 0); dp[0] = 1;
  for (int i = 2; i < n; ++ i) if (vs[i] == 1) {
    pl.push_back(i);
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
  for (int i = 0; i < pl.size(); ++ i) {
    for (int j = pl[i]; j < n; ++ j) {
      dp[j] += dp[j - pl[i]];
    }
  }
  for (int i = 1; i < n; ++ i) {
    if (dp[i] > 5000) return i;
  }
  return -1;
}

int main() {
  cout << sol(1000) << endl;
  return 0;
}

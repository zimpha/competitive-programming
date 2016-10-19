#include <bits/stdc++.h>
using namespace std;
unordered_map<long long, int> dp;

int sol(long long n) {
  if (n == 1) return dp[n] = 1;
  if (dp.count(n)) return dp[n];
  if (n & 1) dp[n] = sol(n * 3 + 1) + 1;
  else dp[n] = sol(n >> 1) + 1;
  return dp[n];
}

int main() {
  int ret(0), mx(0);
  for (int i = 1; i < 1000000; ++ i) {
    if (sol(i) > mx) {
      mx = sol(i);
      ret = i;
    }
  }
  cout << ret << " " << mx << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int dp[51][295426];

LL run() {
  dp[0][0] = 1;
  int s = 0;
  for (int i = 1; i <= 100; ++i) {
    s += i * i; s = min(s, 295425);
    for (int j = min(i, 50); j >= 1; --j) {
      for (int k = s; k >= i * i; --k) {
        dp[j][k] += dp[j - 1][k - i * i];
      }
    }
  }
  LL ret = 0;
  for (int i = 1; i <= s; ++i) {
    if (dp[50][i] == 1) ret += i;
  }
  return ret;
}

int main() {
  cout << run() << endl;
  return 0;
}

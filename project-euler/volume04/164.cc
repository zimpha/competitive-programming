#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dp[20][10][10];

int main() {
  for (int i = 1; i <= 9; ++i) dp[0][0][i] = 1;  
  for (int i = 0; i < 19; ++i) {
    for (int a = 0; a < 10; ++a) {
      for (int b = 0; b < 10; ++b) if (dp[i][a][b]) {
        for (int c = 0; c < 10; ++c) if (a + b + c <= 9) {
          dp[i + 1][b][c] += dp[i][a][b];
        }
      }
    }
  }
  LL ret = 0;
  for (int a = 0; a < 10; ++a) {
    for (int b = 0; b < 10; ++b) {
      ret += dp[19][a][b];
    }
  }
  cout << ret << endl;
  return 0;
}

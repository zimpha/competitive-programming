#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

map<int, LL> dp[21][11];

LL run(int n, int m, int s) {
  if (dp[n][m].count(s)) return dp[n][m][s];
  LL &ret = dp[n][m][s];
  if (n == 20) return ret = (m == 0);
  for (int d = n == 0; d < 10; ++d) {
    int o = s >> (d * 2) & 3;
    if (o == 3) continue;
    if (o == 0) ret += run(n + 1, (m * 10 + d) % 11, s | (1 << (d * 2)));
    if (o == 1) ret += run(n + 1, (m * 10 + d) % 11, s | (1 << (d * 2 + 1)));
  }
  return ret;
}

int main() {
  cout << run(0, 0, 0) << endl;
  return 0;
}

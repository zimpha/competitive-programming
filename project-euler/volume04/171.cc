#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M = 1000000000;

LL f[30][2000], g[30][2000];

int run(int n) {
  int m = n * 9 * 9;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = g[i][j] = 0;
    }
  }
  g[0][0] = 1;
  LL p = 1;
  for (int i = 1; i <= n; ++i) {
    for (int o = 0; o < 10; ++o) {
      for (int j = o * o; j <= i * 9 * 9; ++j) {
        g[i][j] += g[i - 1][j - o * o]; g[i][j] %= M;
        f[i][j] += f[i - 1][j - o * o] * 10 % M + g[i - 1][j - o * o] * o % M;
        f[i][j] %= M;
      }
    }
  }
  LL ret = 0;
  for (int i = 1; i * i <= m; ++i) {
    ret += f[n][i * i]; ret %= M;
  }
  return ret;
}

int main() {
  cout << run(1) << endl;
  cout << run(20) << endl;
  return 0;
}

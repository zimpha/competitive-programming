#include <bits/stdc++.h>

using LL = long long;

LL run(int n, int m, int o, int s) {
  LL f[n + 1][m + 1][n + 1][s + 1];
  memset(f, 0, sizeof(f));
  f[0][m][0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k <= i; ++k) {
        for (int x = 0; x <= s; ++x) {
          if (!f[i - 1][j][k][x]) continue;
          for (int l = 1; l <= j; ++l) {
            int y = x + l * (i <= o);
            int t = (l == j) ? k + 1 : 1;
            if (y <= s) {
              f[i][l][t][y] += f[i - 1][j][k][x] * i / t;
            }
          }
        }
      }
    }
  }
  LL ret = 0;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      ret += f[n][i][j][s];
    }
  }
  return ret;
}

int main() {
  assert(run(5, 6, 3, 15) == 1111);
  std::cout << run(20, 12, 10, 70) << std::endl;
  return 0;
}

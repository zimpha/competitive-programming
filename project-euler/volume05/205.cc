#include <bits/stdc++.h>

double run() {
  int f[10][37], g[7][37];
  memset(f, 0, sizeof(f));
  memset(g, 0, sizeof(g));
  f[0][0] = g[0][0] = 1;
  for (int i = 1; i <= 9; ++i) {
    for (int j = 0; j <= 36; ++j) {
      for (int k = 1; k <= 4; ++k) {
        if (f[i - 1][j] && j + k <= 36) {
          f[i][j + k] += f[i - 1][j];
        }
      }
    }
  }
  for (int i = 1; i <= 6; ++i) {
    for (int j = 0; j <= 36; ++j) {
      for (int k = 1; k <= 6; ++k) {
        if (g[i - 1][j] && j + k <= 36) {
          g[i][j + k] += g[i - 1][j];
        }
      }
    }
  }
  double ret = 0;
  for (int x = 1; x <= 36; ++x) {
    for (int y = 1; y < x; ++y) {
      ret += f[9][x] / 262144.0 * g[6][y] / 46656.0;
    }
  }
  return ret;
}

int main() {
  printf("%.7f\n", run());
  return 0;
}

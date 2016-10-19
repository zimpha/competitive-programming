#include <bits/stdc++.h>

using LL = long long;

double run() {
  LL total = 161884603662657876ll;
  LL f[8][21][8], C[20][20];
  for (int i = 0; i <= 10; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
    }
  }
  memset(f, 0, sizeof(f));
  f[0][0][0] = 1;
  for (int i = 1; i <= 7; ++i) {
    for (int j = 0; j <= 20; ++j) {
      for (int k = 0; k <= i; ++k) {
        for (int d = 0; d <= 10; ++d) {
          if (j >= d && k >= !!d && f[i - 1][j - d][k - !!d]) {
            f[i][j][k] += f[i - 1][j - d][k - !!d] * C[10][d];
          }
        }
      }
    }
  }
  double ret = 0;
  LL sum = 0;
  for (int i = 1; i <= 7; ++i) {
    std::cout << i << ' ' << f[7][20][i] << std::endl;
    sum += f[7][20][i];
    ret += 1.0 * f[7][20][i] / total * i;
  }
  std::cout << total << ' ' << sum << std::endl;
  return ret;
}

int main() {
  std::cout.precision(10);
  std::cout << run() << std::endl;
  return 0;
}

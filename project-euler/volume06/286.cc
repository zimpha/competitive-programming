#include <bits/stdc++.h>

double calc(double q) {
  double f[51][22];
  memset(f, 0, sizeof(f));
  f[0][0] = 1;
  for (int i = 0; i < 50; ++i) {
    for (int j = 0; j <= 20; ++j) {
      if (!f[i][j]) continue;
      double fail = (i + 1) / q, win = 1 - fail;
      f[i + 1][j] += fail * f[i][j];
      f[i + 1][j + 1] += win * f[i][j];
    }
  }
  return f[50][20];
}

double run() {
  double left = 50, right = 100;
  for (int i = 0; i < 100; ++i) {
    double mid = (left + right) * 0.5;
    double prob = calc(mid);
    if (prob < 0.02) right = mid;
    else left = mid;
  }
  return left;
}

int main() {
  std::cout.precision(20);
  std::cout << std::fixed << run() << std::endl;
  return 0;
}


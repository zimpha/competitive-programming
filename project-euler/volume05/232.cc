#include <bits/stdc++.h>

double run() {
  double f[100][100];
  auto get = [&](int x, int y) {
    if (x >= 100) return 0.;
    else if (y >= 100) return 1.;
    else return f[x][y];
  };
  for (int i = 99; i >= 0; --i) {
    for (int j = 99; j >= 0; --j) {
      double p = 1;
      f[i][j] = 0;
      for (int s = 1; s <= 200; s *= 2) {
        p *= 0.5;
        double curr = 0.5 * (1 - p) * get(i + 1, j);
        if (j + s >= 100) curr += p;
        else curr += p * 0.5 * (get(i + 1, j + s) + get(i, j + s));
        f[i][j] = std::max(f[i][j], curr / (1 - (1 - p) * 0.5));
      }
    }
  }
  return (f[0][0] + f[1][0]) / 2;
}

int main() {
  std::cout.precision(10);
  std::cout << run() << std::endl;
  return 0;
}

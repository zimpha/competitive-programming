#include <bits/stdc++.h>

const int N = 46080 + 10;

double x[N], y[N];

double run(std::vector<int> dice) {
  std::vector<double> f = {1};
  int now = 1;
  for (auto &&d: dice) {
    std::vector<double> g(f.size() * d);
    int total = 0;
    x[0] = 1;
    for (int i = 1; i <= now; ++i) {
      for (int j = 0; j <= total + d; ++j) y[j] = 0;
      for (int j = i - 1; j <= total; ++j) {
        for (int k = 1; k <= d; ++k) {
          y[j + k] += x[j] / d;
        }
      }
      total += d;
      for (int j = i; j <= total; ++j) {
        x[j] = y[j];
        g[j - 1] += f[i - 1] * x[j];
      }
    }
    f.swap(g);
    now *= d;
  }
  double e = 0;
  for (int i = 0; i < now; ++i) {
    e += (i + 1) * f[i];
  }
  double ret = 0;
  for (int i = 0; i < now; ++i) {
    ret += f[i] * (i + 1 - e) * (i + 1 - e);
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run({4, 6, 8, 12, 20}) << std::endl;
  return 0;
}

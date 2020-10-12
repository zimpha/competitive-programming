#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &y[i]);
  double best = 1e9, K, B;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      // x[i] = k y[i] + b
      // x[j] = k y[j] + b
      double k = (double)(x[i] - x[j]) / (y[i] - y[j]);
      double b = x[i] - k * y[i];
      double sum = 0;
      for (int t = 0; t < n; ++t) {
        sum += std::abs(x[t] - (k * y[t] + b));
      }
      if (sum < best) {
        best = sum;
        K = k;
        B = b;
      }
    }
  }
  printf("%.20f %.20f %.20f\n", best, K, B);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, T, C;
  scanf("%d%d%d", &n, &T, &C);
  std::vector<int> t(n), c(n);
  int less = 0, greater = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &t[i], &c[i]);
    if (t[i] <= T) ++less;
    if (t[i] >= T) ++greater;
  }
  if (less == n && greater == n) {
    printf("Possible\n%.4f\n", (double)T);
  } else if (less == n) {
    double left = 0, right = T;
    for (int i = 0; i < n; ++i) left = std::max<double>(left, t[i]);
    for (int it = 0; it < 50; ++it) {
      double mid = (left + right) * 0.5;
      double need = 0;
      for (int i = 0; i < n; ++i) {
        need += (t[i] * c[i] - mid * c[i]) / (mid - T);
      }
      if (need <= C) left = mid;
      else right = mid;
    }
    double need = 0;
    for (int i = 0; i < n; ++i) {
      need += (t[i] * c[i] - left * c[i]) / (left - T);
    }
    if (need <= C) printf("Possible\n%.4f\n", left);
    else puts("Impossible");
  } else if (greater == n) {
    double left = T, right = 1e9;
    for (int i = 0; i < n; ++i) right = std::min<double>(right, t[i]);
    for (int it = 0; it < 50; ++it) {
      double mid = (left + right) * 0.5;
      double need = 0;
      for (int i = 0; i < n; ++i) {
        need += (t[i] * c[i] - mid * c[i]) / (mid - T);
      }
      if (need <= C) left = mid;
      else right = mid;
    }
    double need = 0;
    for (int i = 0; i < n; ++i) {
      need += (t[i] * c[i] - left * c[i]) / (left - T);
    }
    if (need <= C) printf("Possible\n%.4f\n", left);
    else puts("Impossible");
  } else {
    puts("Impossible");
  }
  return 0;
}

#include <cstdio>
#include <vector>

int main() {
  int n;
  double u, v;
  scanf("%d%lf%lf", &n, &v, &u);
  std::vector<double> a(n), b(n);
  for (int i = 0; i < n; ++i) scanf("%lf", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%lf", &b[i]);
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ret += u / (a[i] - j * b[i] - v);
    }
  }
  printf("%.3f\n", ret);
  return 0;
}

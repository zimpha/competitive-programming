#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<double> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &x[i], &y[i]);
  }
  double x_a = 1, x_b = 0, y_a = 1, y_b = 0;
  for (int i = 0; i < n; ++i) {
    x_a = -x_a, x_b = x[i] * 2 - x_b;
    y_a = -y_a, y_b = y[i] * 2 - y_b;
  }
  if ((x_a == 1 && x_b != 0) || (y_a == 1 && y_b != 0)) {
    puts("NO");
    return 0;
  }
  double x_0 = 1, y_0 = 1;
  if (x_a == -1) x_0 = x_b / 2;
  if (y_a == -1) y_0 = y_b / 2;
  puts("YES");
  for (int i = 0; i < n; ++i) {
    printf("%.10f %.10f\n", x_0, y_0);
    x_0 = 2 * x[i] - x_0;
    y_0 = 2 * y[i] - y_0;
  }
  return 0;
}

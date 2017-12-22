#include <cmath>
#include <cstdio>

int main() {
  double a, b;
  scanf("%lf%lf", &a, &b);
  printf("%.10f\n", 2 * acos(-1.0) * (b - a));
}

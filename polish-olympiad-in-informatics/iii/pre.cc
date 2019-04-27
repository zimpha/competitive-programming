#include <cstdio>
#include <cmath>

double pi = acos(-1.0);

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int l, d;
    scanf("%d%d", &l, &d);
    double left = l * 0.5, right = 1e7;
    for (int it = 0; it < 40; ++it) {
      double mid = (left + right) * 0.5;
      double theta = asin(l / (mid * 2));
      if (theta * mid < (l + d) * 0.5) right = mid;
      else left = mid;
    }
    printf("%.0f\n", left - sqrt(left * left - 0.25 * l * l));
  }
}

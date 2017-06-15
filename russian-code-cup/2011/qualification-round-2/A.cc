#include <cstdio>
#include <cmath>
#include <vector>

const double pi = acos(-1.0);

int main() {
  int n, r, s = 0;
  scanf("%d%d", &n, &r);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    s += a[i];
  }
  for (int i = 0; i < n; ++i) {
    printf("%.10f\n", r * r * pi * a[i] / s);
  }
  return 0;
}

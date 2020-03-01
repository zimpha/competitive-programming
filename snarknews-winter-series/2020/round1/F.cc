#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<double> f(m + 1);
  double mx = 0;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[i] += std::max<double>(j, f[i - 1]);
    }
    f[i] /= n;
    mx = std::max(mx, f[i]);
  }
  printf("%.10f\n", mx);
  return 0;
}

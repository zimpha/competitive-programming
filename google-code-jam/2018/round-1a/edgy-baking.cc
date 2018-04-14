#include <cstdio>
#include <cmath>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, p;
    scanf("%d%d", &n, &p);
    std::vector<int> w(n), h(n);
    int m = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &w[i], &h[i]);
      if (w[i] > h[i]) std::swap(w[i], h[i]);
      m += w[i];
      sum += 2 * w[i] + 2 * h[i];
    }
    std::vector<double> f(m + 1);
    for (int i = 0; i < n; ++i) {
      double len = hypot(w[i], h[i]);
      for (int j = m; j >= w[i]; --j) {
        f[j] = std::max(f[j], len + f[j - w[i]]);
      }
    }
    double ret = sum;
    for (int i = 0; i <= m; ++i) if (f[i] >= i) {
      double l = i * 2, r = f[i] * 2, rest = p - sum;
      double now = sum;
      if (rest >= l) {
        if (rest <= r) now = p;
        else now += r;
      }
      ret = std::max(ret, now);
    }
    printf("Case #%d: %.10f\n", cas, ret);
  }
  return 0;
}

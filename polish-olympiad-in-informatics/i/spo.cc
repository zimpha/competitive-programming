#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<double> a(n);
  for (int i = 0; i < n; ++i) scanf("%lf", &a[i]);
  std::reverse(a.begin(), a.end());
  std::vector<double> g(n + 1, -1);
  int ret = 0;
  for (auto &&t: a) {
    if (t > g[ret]) g[++ret] = t;
    else {
      int l = 1, r = ret;
      while (l <= r) {
        int m = (l + r) >> 1;
        if (t > g[m]) l = m + 1;
        else r = m - 1;
      }
      g[l] = t;
    }
  }
  printf("%d00\n", ret);
  return 0;
}

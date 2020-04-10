#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  std::vector<int> f(n), g(n);
  for (int i = 0; i < n; ++i) {
    f[i] = a[i];
    if (i) f[i] = std::max(f[i], f[i - 1]);
  }
  for (int i = n - 1; i >= 0; --i) {
    g[i] = a[i];
    if (i + 1 < n) g[i] = std::max(g[i], g[i + 1]);
  }
  long long ret = 0;
  for (int i = 2; i + 2 < n; ++i) {
    ret = std::max(ret, 1ll * f[i - 2] + a[i] + g[i + 2]);
  }
  printf("%lld\n", ret);
  return 0;
}

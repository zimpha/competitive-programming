#include <cstdio>
#include <vector>

const int mod = 30011;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<unsigned int> f(m + 1, 1), g(m + 1);
  for (int i = 2; i <= n; ++i) {
    g = f;
    for (int j = 0; j <= m; ++j) {
      if (j >= i) g[j] += mod - f[j - i];
      if (g[j] >= mod) g[j] -= mod;
    }
    f.swap(g);
    for (int j = 1; j <= m; ++j) {
      f[j] += f[j - 1];
      if (f[j] >= mod) f[j] -= mod;
    }
  }
  printf("%d\n", ((int)f[m] + mod - (m > 0 ? f[m - 1] : 0)) % mod);
  return 0;
}

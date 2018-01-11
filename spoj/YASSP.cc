#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m = 0;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      m += a[i];
    }
    std::vector<int64> f(m + 1), g(m + 1);
    f[0] = 1;
    for (auto &&x: a) {
      g = f;
      for (int i = 0; i + x <= m; ++i) if (f[i]) {
        g[i + x] |= f[i] << 1;
      }
      f.swap(g);
    }
    int mx = 0, ret = 0;
    for (int x = 1; x <= m; ++x) {
      int cnt = __builtin_popcountll(f[x]);
      if (cnt > mx) mx = cnt, ret = x;
    }
    printf("%d %d\n", mx, ret);
  }
  return 0;
}

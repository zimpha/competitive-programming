#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]), --a[i];
    std::vector<int> f(7, 1), g(7);
    f[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
      g.assign(7, -1);
      for (int x = 0; x < 7; ++x) {
        for (int y = x - 1; y < 7 && y <= x + 1; ++y) {
          if (y < 0) continue;
          if (g[x] == -1 || g[x] > f[y] + (x != a[i])) {
            g[x] = f[y] + (x != a[i]);
          }
        }
      }
      f.swap(g);
    }
    printf("%d\n", *std::min_element(f.begin(), f.end()));
  }
  return 0;
}

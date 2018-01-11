#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 5000 + 10;

int f[N][2], g[N][2];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i + 1 < n; ++i) {
      a[i] = a[i + 1] - a[i];
    }
    for (int i = 0; i <= m; ++i) {
      f[i][0] = f[i][1] = -1;
    }
    auto update = [] (int &x, int y) {
      x = std::max(x, y);
    };
    f[0][0] = 0;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j <= m; ++j) {
        g[j][0] = g[j][1] = -1;
      }
      for (int j = 0; j <= m; ++j) {
        if (f[j][0] != -1) {
          if (j + a[i] <= m) {
            update(g[j + a[i]][1], f[j][0] + 1);
          }
          update(g[j][0], f[j][0]);
        }
        if (f[j][1] != -1) {
          update(g[j][0], f[j][1]);
        }
      }
      for (int j = 0; j <= m; ++j) {
        f[j][0] = g[j][0];
        f[j][1] = g[j][1];
      }
    }
    int ret = 0;
    for (int i = 0; i <= m; ++i) {
      ret = std::max(ret, std::max(f[i][0], f[i][1]));
    }
    printf("Case %d: %d\n", cas, ret * 2);
  }
  return 0;
}

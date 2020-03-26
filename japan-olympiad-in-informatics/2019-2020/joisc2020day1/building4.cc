#include <cstdio>
#include <cassert>
#include <vector>

const int N = 1e6 + 10;

char ret[N];
int val[N][2], f[N][2], g[N][2];

int main() {
  int n;
  scanf("%d", &n);
  for (int e = 0; e < 2; ++e) {
    for (int i = 0; i < n * 2; ++i) {
      scanf("%d", &val[i][e]);
    }
  }
  f[0][0] = g[0][0] = 1;
  f[0][1] = g[0][1] = 0;
  for (int i = 1; i < n * 2; ++i) {
    f[i][0] = +1e9, f[i][1] = +1e9;
    g[i][0] = -1e9, g[i][1] = -1e9;
    for (int x = 0; x < 2; ++x) for (int y = 0; y < 2; ++y) if (val[i][x] >= val[i - 1][y]) {
      int w = x == 0;
      if (g[i - 1][y] + w > g[i][x]) g[i][x] = g[i - 1][y] + w;
      if (f[i - 1][y] + w < f[i][x]) f[i][x] = f[i - 1][y] + w;
    }
  }
  int choose = 0;
  if (f[n * 2 - 1][0] > n || g[n * 2 - 1][0] < n) ++choose;
  if (f[n * 2 - 1][choose] > n || g[n * 2 - 1][choose] < n) {
    puts("-1");
    return 0;
  }
  int need = n;
  for (int i = n * 2 - 1; i >= 0; --i) {
    ret[i] = choose + 'A';
    need -= choose == 0;
    if (i) {
      bool found = false;
      for (int x = 0; x < 2; ++x) if (val[i][choose] >= val[i - 1][x]) {
        if (f[i - 1][x] <= need && need <= g[i - 1][x]) {
          choose = x;
          found = true;
          break;
        }
      }
      assert(found);
    }
  }
  ret[n * 2] = 0;
  puts(ret);
  return 0;
}

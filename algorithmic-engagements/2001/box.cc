#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> out_x(2 * (n + m)), out_y(2 * (n + m));
  for (int i = 0; i < 2 * (n + m); ++i) {
    int x;
    scanf("%d", &x);
    if (x <= n) out_x[i] = x - 1, out_y[i] = 0;
    else if (x <= n + m) out_x[i] = n - 1, out_y[i] = x - 1;
    else if (x <= n * 2 + m) out_x[i] = n * 2 + m - x, out_y[i] = m;
    else out_x[i] = -1, out_y[i] = n * 2 + m * 2 - x;
  }
  std::vector<std::vector<int>> box(n, std::vector<int>(m, 0));
  for (int i = 0; i < n + m; ++i) {
    int x, y, dir;
    if (i < n) x = i, y = 0, dir = 0;
    else x = n - 1, y = i - n, dir = 1;
    int xx = out_x[i], yy = out_y[i];
    while (x != xx || y != yy) {
      if (dir == 0) {
        bool above = false;
        for (int j = 0; j < x; ++j) above |= box[j][y];
        if ((!above && y != yy) || x == xx) ++y;
        else {
          box[x][y] = 1;
          --x;
          dir = 1;
        }
      } else {
        if (box[x][y]) ++y, dir = 0;
        else --x;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j) putchar(' ');
      printf("%d", box[i][j]);
    }
    puts("");
  }
  return 0;
}

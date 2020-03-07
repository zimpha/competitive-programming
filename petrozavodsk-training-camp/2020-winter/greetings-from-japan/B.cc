#include <cstdio>
#include <algorithm>

const int N = 100;

int low[N][N];
int upp[N][N];

int main() {
  int w, d, n;
  scanf("%d%d%d", &w, &d, &n);
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < d; ++j) {
      low[i][j] = -1000;
      upp[i][j] = 1000;
    }
  }
  for (int i = 0; i < n; ++i) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    --x, --y;
    for (int xx = 0; xx < w; ++xx) {
      for (int yy = 0; yy < d; ++yy) {
        int delta = std::abs(x - xx) + std::abs(y - yy);
        low[xx][yy] = std::max(low[xx][yy], z - delta);
        upp[xx][yy] = std::min(upp[xx][yy], z + delta);
      }
    }
  }
  int ret = 0, valid = true;
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < d; ++j) {
      if (low[i][j] <= upp[i][j]) ret += low[i][j];
      else valid = false;
    }
  }
  if (valid) printf("%d\n", ret);
  else puts("No");
  return 0;
}

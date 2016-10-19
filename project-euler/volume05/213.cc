#include <bits/stdc++.h>

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

double run(int n, int m) {
  double f[n][n], g[n][n], p[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      p[i][j] = 1;
    }
  }
  for (int s = 0; s < n; ++s) {
    for (int t = 0; t < n; ++t) {
      memset(f, 0, sizeof(f));
      f[s][t] = 1;
      for (int i = 0; i < m; ++i) {
        memset(g, 0, sizeof(g));
        for (int x = 0; x < n; ++x) {
          for (int y = 0; y < n; ++y) {
            if (!f[x][y]) continue;
            int tot = 4;
            if (x == 0 || x == n - 1) --tot;
            if (y == 0 || y == n - 1) --tot;
            for (int k = 0; k < 4; ++k) {
              int xx = x + dx[k], yy = y + dy[k];
              if (xx < 0 || xx == n || yy < 0 || yy == n) continue;
              g[xx][yy] += f[x][y] / tot;
            }
          }
        }
        memcpy(f, g, sizeof(g));
      }
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          p[x][y] *= 1.0 - f[x][y];
        }
      }
    }
  }
  double ret = 0;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      ret += p[x][y];
    }
  }
  return ret;
}

int main() {
  std::cout.precision(6);
  std::cout << std::fixed << run(30, 50) << std::endl;
  return 0;
}
